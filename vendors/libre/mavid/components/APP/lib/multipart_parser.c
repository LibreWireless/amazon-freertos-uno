/* Based on node-formidable by Felix Geisendörfer
 * Igor Afonov - afonov@gmail.com - 2012
 * MIT License - http://www.opensource.org/licenses/mit-license.php
 */


#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "lib.h"

#include "multipart_parser.h"


//#define DEBUG_MULTIPART



static void multipart_log(char * format, ...)
{
#ifdef DEBUG_MULTIPART
    va_list args;
    va_start(args, format);

    fprintf(stdout, "[HTTP_MULTIPART_PARSER] %s:%d: ", __FILE__, __LINE__);
    vfprintf(stdout, format, args);
    fprintf(stdout, "\n");
#endif
}

#define NOTIFY_CB(FOR)                                                 \
do {                                                                   \
  if (p->settings->on_##FOR) {                                         \
    if (p->settings->on_##FOR(p) != 0) {                               \
      return i;                                                        \
    }                                                                  \
  }                                                                    \
} while (0)

#define EMIT_DATA_CB(FOR, ptr, len)                                    \
do {                                                                   \
  if (p->settings->on_##FOR) {                                         \
    if (p->settings->on_##FOR(p, ptr, len) != 0) {                     \
      return i;                                                        \
    }                                                                  \
  }                                                                    \
} while (0)


#define LF 10
#define CR 13

struct parsed_info_t {
    int content_disposition,content_disposition_metadata_match,content_disposition_audio_match;
    int content_type, content_type_json_match,content_type_octect_stream_match;
    char* json_data_begin;
    int json_data_len;
    char* octect_data_begin;
    int octect_data_len;
};

struct multipart_parser {
    void * data;

    size_t index;
    size_t boundary_length;

    unsigned char state;

    multipart_parser_settings* settings;

    char* lookbehind;
    struct parsed_info_t parsed_info;
    char multipart_boundary[1];
};

enum state {
    s_uninitialized = 1,
    s_start,
    s_start_boundary,
    s_header_field_start,
    s_header_field,
    s_headers_almost_done,
    s_header_value_start,
    s_header_value,
    s_header_value_almost_done,
    s_part_data_start,
    s_part_data,
    s_part_data_almost_boundary,
    s_part_data_boundary,
    s_part_data_almost_end,
    s_part_data_end,
    s_part_data_final_hyphen,
    s_end
};

multipart_parser* multipart_parser_init(char *boundary,
                                        multipart_parser_settings* settings)
{
    multipart_parser* p = safe_malloc((sizeof(multipart_parser) +
                                       strlen(boundary) +
                                       strlen(boundary) + 9),1);

    memset(&p->parsed_info, 0, sizeof(struct multipart_parser));
    strcpy(p->multipart_boundary, boundary);
    p->boundary_length = strlen(boundary);

    p->lookbehind = (p->multipart_boundary + p->boundary_length + 1);

    p->index = 0;
    p->state = s_start;
    p->settings = settings;

    return p;
}

void multipart_parser_free(multipart_parser* p) {
    free(p);
}

void multipart_parser_set_data(multipart_parser *p, void *data) {
    p->data = data;
}

void *multipart_parser_get_data(multipart_parser *p) {
    return p->data;
}

size_t multipart_parser_execute(multipart_parser* p, char *buf, size_t len) {
    size_t i = 0;
    size_t mark = 0;
    char c, cl;
    int is_last = 0;

#ifdef ENABLE_MULTIPART_PARSER_DBG_PRINTS
    printf("Multipart parser execute\n");
#endif


    while(i < len) {
        c = buf[i];
        is_last = (i == (len - 1));
        switch (p->state) {
        case s_start:
            multipart_log("s_start");
            p->index = 0;
            p->state = s_start_boundary;

        /* fallthrough */
        case s_start_boundary:
            multipart_log("s_start_boundary");
            if (p->index == p->boundary_length) {
                if (c != CR) {
                    //multipart_log("not CR");
                    return i;
                }
                p->index++;
                break;
            } else if (p->index == (p->boundary_length + 1)) {
                if (c != LF) {
                    //multipart_log("not LF");
                    return i;
                }
                p->index = 0;
                NOTIFY_CB(part_data_begin);
                p->state = s_header_field_start;
                break;
            }
            if (c != p->multipart_boundary[p->index]) {
                //multipart_log("mistmatch: %d",p->index);
                return i;
            }
            //multipart_log("%d",p->index);
            p->index++;
            break;

        case s_header_field_start:
            multipart_log("s_header_field_start");
            mark = i;
            p->state = s_header_field;

        /* fallthrough */
        case s_header_field:
            multipart_log("s_header_field");
            if (c == CR) {
                p->state = s_headers_almost_done;
                break;
            }

            if (c == ':') {
                EMIT_DATA_CB(header_field, buf + mark, i - mark);
                p->state = s_header_value_start;
                break;
            }

            cl = tolower(c);
            if ((c != '-') && (cl < 'a' || cl > 'z')) {
                multipart_log("invalid character in header name");
                return i;
            }
            if (is_last)
                EMIT_DATA_CB(header_field, buf + mark, (i - mark) + 1);
            break;

        case s_headers_almost_done:
            multipart_log("s_headers_almost_done");
            if (c != LF) {
                return i;
            }

            p->state = s_part_data_start;
            break;

        case s_header_value_start:
            multipart_log("s_header_value_start");
            if (c == ' ') {
                break;
            }

            mark = i;
            p->state = s_header_value;

        /* fallthrough */
        case s_header_value:
            multipart_log("s_header_value");
            if (c == CR) {
                EMIT_DATA_CB(header_value, buf + mark, i - mark);
                p->state = s_header_value_almost_done;
                break;
            }
            if (is_last)
                EMIT_DATA_CB(header_value, buf + mark, (i - mark) + 1);
            break;

        case s_header_value_almost_done:
            multipart_log("s_header_value_almost_done");
            if (c != LF) {
                return i;
            }
            p->state = s_header_field_start;
            break;

        case s_part_data_start:
            multipart_log("s_part_data_start");
            NOTIFY_CB(headers_complete);
            mark = i;
            p->state = s_part_data;

        /* fallthrough */
        case s_part_data:
            multipart_log("s_part_data");
            if (c == CR) {
                EMIT_DATA_CB(part_data, buf + mark, i - mark);
                mark = i;
                p->state = s_part_data_almost_boundary;
                p->lookbehind[0] = CR;
                break;
            }
            if (is_last)
                EMIT_DATA_CB(part_data, buf + mark, (i - mark) + 1);
            break;

        case s_part_data_almost_boundary:
            multipart_log("s_part_data_almost_boundary");
            if (c == LF) {
                p->state = s_part_data_boundary;
                p->lookbehind[1] = LF;
                p->index = 0;
                break;
            }
            EMIT_DATA_CB(part_data, p->lookbehind, 1);
            p->state = s_part_data;
            mark = i --;
            break;

        case s_part_data_boundary:
            multipart_log("s_part_data_boundary");
            if (p->multipart_boundary[p->index] != c) {
                EMIT_DATA_CB(part_data, p->lookbehind, 2 + p->index);
                p->state = s_part_data;
                mark = i --;
                break;
            }
            p->lookbehind[2 + p->index] = c;
            if ((++ p->index) == p->boundary_length) {
                NOTIFY_CB(part_data_end);
                p->state = s_part_data_almost_end;
            }
            break;

        case s_part_data_almost_end:
            multipart_log("s_part_data_almost_end");
            if (c == '-') {
                p->state = s_part_data_final_hyphen;
                break;
            }
            if (c == CR) {
                p->state = s_part_data_end;
                break;
            }
            return i;

        case s_part_data_final_hyphen:
            multipart_log("s_part_data_final_hyphen");
            if (c == '-') {
                NOTIFY_CB(body_end);
                p->state = s_end;
                break;
            }
            return i;

        case s_part_data_end:
            multipart_log("s_part_data_end");
            if (c == LF) {
                p->state = s_header_field_start;
                NOTIFY_CB(part_data_begin);
                break;
            }
            return i;

        case s_end:
            multipart_log("s_end: %02X", (int) c);
            break;

        default:
            multipart_log("Multipart parser unrecoverable error");
            return 0;
        }
        ++ i;
    }

    return len;
}


#define HDR "Content-Type"


int read_header_name(multipart_parser* p, char *at, size_t length)
{
    struct parsed_info_t *parsed_info = &p->parsed_info;
#ifdef ENABLE_MULTIPART_PARSER_DBG_PRINTS
    printf("\nheader name. length=%d,  |%.*s|", length, length, at);
#endif
    if(strncasecmp(HDR, at, length) == 0)
    {
        parsed_info->content_type=1;
    }
    else
    {
#ifdef ENABLE_MULTIPART_PARSER_DBG_PRINTS
        printf("unknown header name..\n");
#endif
        parsed_info->content_type=0;
    }
    return 0;
}

#define HDR_VAL1 "application/json; charset=UTF-8"
#define HDR_VAL2 "application/octet-stream"

int read_header_value(multipart_parser* p, char *at, size_t length)
{
    struct parsed_info_t *parsed_info = &p->parsed_info;
#ifdef ENABLE_MULTIPART_PARSER_DBG_PRINTS
    printf("\nheader value. length=%d, |%.*s|\n", length, length, at);
#endif
    if(parsed_info->content_type==1)
    {
        if(strncasecmp(HDR_VAL1, at, length) == 0)
        {
            parsed_info->content_type_json_match=1;
            parsed_info->content_type=0;
        }
        else if(strncasecmp(HDR_VAL2, at, length) == 0)
        {
            parsed_info->content_type_octect_stream_match=1;
            parsed_info->content_type=0;
        }
        else
        {
#ifdef ENABLE_MULTIPART_PARSER_DBG_PRINTS
            printf("content type wrong val\n");
#endif
        }
    }
    else
    {
#ifdef ENABLE_MULTIPART_PARSER_DBG_PRINTS
        printf("unknown header value..\n");
#endif
    }

    return 0;
}


int read_header_data(multipart_parser* p, char *at, size_t length)
{
    int retval=0;
    struct parsed_info_t *parsed_info = &p->parsed_info;
#ifdef ENABLE_MULTIPART_PARSER_DBG_PRINTS
    printf("\nheader data. len=%d, |%.*s|\n", length,length, at);
#endif
    if(parsed_info->content_type_json_match==1)
    {
        parsed_info->json_data_begin=at;
        parsed_info->json_data_len=length;
        parsed_info->content_type_json_match=0;
#ifdef NEW_MULTIPART_PARSER
        retval = 1;
#endif
    }
    else if(parsed_info->content_type_octect_stream_match==1)
    {
        parsed_info->octect_data_begin=at;
        parsed_info->octect_data_len=length;
        parsed_info->content_type_octect_stream_match=0;
#ifdef ENABLE_MULTIPART_PARSER_DBG_PRINTS
        printf("\nStart of Octect stream data... returning 1, stopping parsing..\n");
#endif
        retval=1;
    }
    else
    {
#ifdef ENABLE_MULTIPART_PARSER_DBG_PRINTS
        printf("unknown header data.. len=%d\n",length);
#endif
    }
    return retval;
}


void check_for_complete_multipart_data(char* msg,
                                       char* boundary, int msgLen,
                                       int* json_offset, int* json_len,
                                       int* octect_offset, int *octect_len)
{
    multipart_parser_settings callbacks;
    memset(&callbacks, 0, sizeof(multipart_parser_settings));

    if(json_offset)   *json_offset=0;
    if(json_len)      *json_len=0;
    if(octect_offset) *octect_offset=0;
    if(octect_len)    *octect_len=0;

    callbacks.on_header_field = read_header_name;
    callbacks.on_header_value = read_header_value;
    callbacks.on_part_data = read_header_data;

    multipart_parser* parser = multipart_parser_init(boundary, &callbacks);
    multipart_parser_execute(parser, msg,msgLen);

    if(json_len)
        *json_len=parser->parsed_info.json_data_len;

    if(octect_len)
        *octect_len=parser->parsed_info.octect_data_len;

    if(json_offset)
    {
        if(parser->parsed_info.json_data_begin!=NULL)
            *json_offset=parser->parsed_info.json_data_begin-msg;
    }

    if(octect_offset)
    {
        if(parser->parsed_info.octect_data_begin!=NULL)
            *octect_offset=parser->parsed_info.octect_data_begin-msg;
    }

    multipart_parser_free(parser);
}

#include "avs.h"

char* extract_json_data(char* msg, int offset, int len)
{
    char *temp;

    if(len > (AVS_NETWORK_RX_LEN*MULTIPART_MAX_RECVS))
    {
        //safety chk.
        //printf("json_msg_size=%d. msg=|%.*s|\n",len, len,(msg+offset));
        //fatal("extract_json_data: something wrong in json msg. size unexpectadly high");
    }
    temp=safe_malloc(len+2,1);
    memcpy(temp,msg+offset,len);
    temp[len] = '\0';
    return temp;
}


#ifdef NEW_MULTIPART_PARSER

int extract_multipart_body(char* msg, int msgLen,
                           char* boundary,
                           int stream_id, char* rx_buffer,
                           int *extra_recv, int* extra_recv_sizes,
                           char **multipart_msg, json_t ** root,
                           int *msg_start_offset, int *msg_length)
{
    int json_offset, json_len, octect_offset,octect_len;
    char *pmsg = msg;
    int num_msgs=0;
    int msg_type=MULTIPART_MSG_TYPE_JSON;
    char *json_msg;
    int continue_processing;
    json_t *json_root=NULL;

    if(msgLen<=0)
    {
        fatal("extract_multipart_body: msg len 0... \n\n");
    }

    do
    {
        *multipart_msg=0;
        *msg_start_offset=0;
        *msg_length=0;
        continue_processing=0;
        json_msg=NULL;

#ifdef ENABLE_MULTIPART_PARSER_DBG_PRINTS
        printf("\n\n------------extract_multipart_body:len=%d,stream=%d,msg=|%.*s|---------------\n\n",msgLen,stream_id,msgLen,pmsg);
#endif
        //hexDump(0, pmsg, msgLen);

        check_for_complete_multipart_data(pmsg,boundary,msgLen,
                                          &json_offset, &json_len, &octect_offset, &octect_len);
        if(octect_len!=0)
        {
            // octect started.
            msg_type=MULTIPART_MSG_TYPE_OCTECT_DATA;
#ifdef ENABLE_MULTIPART_PARSER_DBG_PRINTS
            printf("extract_multipart_body: octect data; offset=%d,len=%d, num_msgs=%d,stream=%d\n",
                   octect_offset,octect_len,num_msgs,stream_id);
#endif
            *msg_start_offset=octect_offset;
            *msg_length=octect_len;
            break;
        }

        if(json_len==0)
        {
#ifdef ENABLE_MULTIPART_PARSER_DBG_PRINTS
            printf("extract_multipart_body: json len=0..!!stream=%d",stream_id);
#endif
            if((pmsg[msgLen-1]==0x0d) && (pmsg[msgLen]==0x0a))
            {
                fatal("parsing err..!!");
            }
            else
            {
#ifdef ENABLE_MULTIPART_PARSER_DBG_PRINTS
                printf("not ended with 0d 0a... looks like truncated. processing further.stream_id=%d\n",stream_id);
#endif
                continue_processing=1;
            }
        }
        else
        {
            printf("extract_multipart_body: json msg: offset=%d, len=%d, stream=%d\n",json_offset,json_len,stream_id);
            json_msg = extract_json_data(pmsg, json_offset, json_len);
            *msg_start_offset=json_offset;
            *multipart_msg = json_msg;
            *msg_length = json_len;

            // verify if truncated json
            json_root=chk_for_complete_json_msg(json_msg);
            if(json_root != NULL)
            {
#ifdef ENABLE_MULTIPART_PARSER_DBG_PRINTS
                printf("JSON received completely... returning, num_msgs=%d,stream=%d\n",num_msgs,stream_id);
#endif
                break;
            }
            else
            {
                continue_processing=1;
            }
        }

        if(continue_processing==1)
        {
            // read once again, and try to parse.
            char *temp;
            num_msgs++;
            if(num_msgs>MULTIPART_MAX_RECVS) fatal("too many recvs... something wrong...\n");
#ifdef ENABLE_MULTIPART_PARSER_DBG_PRINTS
            printf("propbably, partial JSON recvd. continuing.. num_msgs=%d,stream=%d\n",num_msgs,stream_id);
#endif            // probably incomplete data.
            if(json_msg != NULL)
                free(json_msg);
            temp=safe_malloc((msgLen+(num_msgs*AVS_NETWORK_RX_LEN)),1);
            memcpy(temp, pmsg, msgLen);
            if(num_msgs>1)
            {
                free(pmsg);
            }
            int rxDataLen = avs_http2_wait_for_data(stream_id);
#ifdef NETWORK_FAILURE_RECOVERY
            if(-1==rxDataLen)
            {
                if(temp)
                    free(temp);
                return MULTIPART_MSG_MULTIPART_MSG_END;
            }
#endif
            if(rxDataLen==0)
            {
#ifdef ENABLE_MULTIPART_PARSER_DBG_PRINTS
                printf("multipart rx returned 0. returning MULTIPART_MSG_MULTIPART_MSG_END. stream=%d\n",stream_id);
#endif
                if(temp)
					free(temp);
				
                return (int)MULTIPART_MSG_MULTIPART_MSG_END;
            }
            extra_recv_sizes[num_msgs-1]=rxDataLen;
            memcpy(temp+msgLen, rx_buffer, rxDataLen);
            msgLen+=rxDataLen;
            pmsg=temp;
#ifdef ENABLE_MULTIPART_PARSER_DBG_PRINTS
            printf("complete json not recvd. continuing.. num_msgs=%d, new_rx=%d,msgLen=%d,stream=%d",
                   num_msgs,rxDataLen,msgLen,stream_id);
#endif
        }
    } while(1);

    if(num_msgs>=1)
        free(pmsg);

    *root=json_root;
    *extra_recv=num_msgs;
    return (int)msg_type;
}

#endif /* NEW_MULTIPART_PARSER */

#if 0



#define BOUNDARY1 "--0c92b030-56db-4f6c-9b1e-4e2af0c0bf86"
#define MSG1 \
"--0c92b030-56db-4f6c-9b1e-4e2af0c0bf86\r\n" \
"Content-Type: application/json; charset=UTF-8\r\n" \
"\r\n" \
"{\"directive\":{\"header\":{\"namespace\":\"SpeechSynthesizer\",\"name\":\"Speak\",\"messageId\":\"9bdfd405-875b-49ec-9baf-647527dd58ba\",\"dialogRequestId\":\"dialog-request-id-1\"},\"payload\":{\"url\":\"cid:KnowledgePrompt.ef726240-89fc-4ed8-b60e-ea9afc1ac3cb_1397841435\",\"format\":\"AUDIO_MPEG\",\"token\":\"amzn1.as-ct.v1.Domain:Application:Knowledge#ACRI#KnowledgePrompt.ef726240-89fc-4ed8-b60e-ea9afc1ac3cb\"}}}\r\n" \
"--0c92b030-56db-4f6c-9b1e-4e2af0c0bf86\r\n" \
"Content-ID: <KnowledgePrompt.ef726240-89fc-4ed8-b60e-ea9afc1ac3cb_1397841435>\r\n" \
"Content-Type: application/octet-stream\r\n" \
"\r\n" \
"asdfasdfqwerqwerasdfasdfasdfasdfasdfasdf"


#define BOUNDARY2 "--854873ff-ac23-4ebd-b329-00bd8cccd94a"
#define MSG2 \
"--854873ff-ac23-4ebd-b329-00bd8cccd94a\r\n" \
"Content-Type: application/json; charset=UTF-8\r\n" \
"\r\n" \
"{\"directive\":{\"header\":{\"namespace\":\"SpeechSynthesizer\",\"name\":\"Speak\",\"messageId\":\"019a5d54-d571-4e0a-a9bd-695d97eec2ad\",\"dialogRequestId\":\"dialog-request-id-4\"},\"payload\":{\"url\":\"cid:WhatsUpActioncf5a4f75-be62-4305-a10b-f53085f261af_1668927456\",\"format\":\"AUDIO_MPEG\",\"token\":\"amzn1.as-ct.v1.Domain:Application:Zeitgeist:Knight:WhatsUp#ACRI#WhatsUpActioncf5a4f75-be62-4305-a10b-f53085f261af\"}}}\r\n" \
"--854873ff-ac23-4ebd-b329-00bd8cccd94a\r\n" \
"Content-Type: application/json; charset=UTF-8\r\n" \
"\r\n" \
"{\"directive\":{\"header\":{\"namespace\":\"SpeechSynthesizer\",\"name\":\"Speak\",\"messageId\":\"d96dc0a1-685c-4145-882e-f8b585c841e0\",\"dialogRequestId\":\"dialog-request-id-4\"},\"payload\":{\"url\":\"cid:WhatsUpActionb00cf3ba-778f-47c7-9e30-16cca1bd2235_1731975007\",\"format\":\"AUDIO_MPEG\",\"token\":\"amzn1.as-ct.v1.Domain:Application:Zeitgeist:Knight:WhatsUp#ACRI#WhatsUpActionb00cf3ba-778f-47c7-9e30-16cca1bd2235\"}}}\r\n" \
"--854873ff-ac23-4ebd-b329-00bd8cccd94a\r\n" \
"Content-Type: application/json; charset=UTF-8\r\n" \
"\r\n" \
"{\"directive\":{\"header\":{\"namespace\":\"SpeechSynthesizer\",\"name\":\"Speak\",\"messageId\":\"c6f5e385-2e4d-4e2c-afd4-540d6bbbb13a\",\"dialogRequestId\":\"dialog-request-id-4\"},\"payload\":{\"url\":\"cid:WhatsUpAction4034783b-d206-4bc0-8ec3-936da620dc65_1359737806\",\"format\":\"AUDIO_MPEG\",\"token\":\"amzn1.as-ct.v1.Domain:Application:Zeitgeist:Knight:WhatsUp#ACRI#WhatsUpAction4034783b-d206-4bc0-8ec3-936da620dc65\"}}}\r\n" \
"--854873ff-ac23-4ebd-b329-00bd8cccd94a\r\n" \
"Content-Type: application/json; charset=UTF-8\r\n" \
"\r\n" \
"{\"directive\":{\"header\":{\"namespace\":\"SpeechSynthesizer\",\"name\":\"Speak\",\"messageId\":\"b101c690-3430-4d83-9892-eb3b38f60e71\",\"dialogRequestId\":\"dialog-request-id-4\"},\"payload\":{\"url\":\"cid:WhatsUpActionbc0c9060-b317-4112-8f7f-de03d0d533df_98429392\",\"format\":\"AUDIO_MPEG\",\"token\":\"amzn1.as-ct.v1.Domain:Application:Zeitgeist:Knight:WhatsUp#ACRI#WhatsUpActionbc0c9060-b317-4112-8f7f-de03d0d533df\"}}}\r\n" \
"--854873ff-ac23-4ebd-b329-00bd8cccd94a\r\n" \
"Content-Type: application/json; charset=UTF-8\r\n" \
"\r\n" \
"{\"directive\":{\"header\":{\"namespace\":\"SpeechRecognizer\",\"name\":\"ExpectSpeech\",\"messageId\":\"4d2974b4-105d-4d44-a4c6-e87430900302\",\"dialogRequestId\":\"dialog-request-id-4\"},\"payload\":{\"timeoutInMilliseconds\":8000}}}\r\n" \
"--854873ff-ac23-4ebd-b329-00bd8cccd94a\r\n" \
"Content-ID: <WhatsUpActioncf5a4f75-be62-4305-a10b-f53085f261af_1668927456>\r\n" \
"Content-Type: application/octet-stream\r\n" \
"\r\n" \
"ID3qwerqwerqwerqwerqwerqwer"


#define BOUNDARY "--------abcde123"
#define MSG \
"--------abcde123\r\n" \
"Content-Type: application/json\r\n" \
"\r\n" \
"{\"directive\":{\"header\":{\"namespace\":\"SpeechRecognizer\",\"name\":\"StopCapture\",\"messageId\":\"3c082eb9-8c71-4f56-a666-9ec82b082bb7\"},\"payload\":{}}}\r\n" \
"--------abcde123\r\n"


#define BOUNDARY4 "--0c92b030-56db-4f6c-9b1e-4e2af0c0bf86"
#define MSG4 \
"--0c92b030-56db-4f6c-9b1e-4e2af0c0bf86\r\n" \
"Content-Type: application/json; charset=UTF-8\r\n" \
"\r\n" \
"{\"directive\":{\"header\":{\"namespace\":\"SpeechSynthesizer\",\"name\":\"Speak\",\"messageId\":\"9bdfd405-875b-49ec-9baf-647527dd58ba\",\"dialogRequestId\":\"dialog-request-id-1\"},\"payload\":{\"url\":\"cid:KnowledgePrompt.ef726240-89fc-4ed8-b60e-ea9afc1ac3cb_1397841435\",\"format\":\"AUDIO_MPEG\",\"token\":\"amzn1.as-ct.v1.Domain:Application:Knowledge#ACRI#KnowledgePrompt.ef726240-89fc-4ed8-b60e-ea9afc1ac3cb\"}}}\r\n" \
"--0c92b030-56db-4f6c-9b1e-4e2af0c0bf86\r\n" \
"Content-ID: <KnowledgePrompt.ef726240-89fc-4ed8-b60e-ea9afc1ac3cb_1397841435>\r\n" \
"Content-Type: application/octet-stream\r\n" \
"\r\n" \
"asdfasdfqwerqwerasdfasdfasdfasdfasdfasdf"




#define BOUNDARY5 "--854873ff-ac23-4ebd-b329-00bd8cccd94a"
#define MSG5 \
"--854873ff-ac23-4ebd-b329-00bd8cccd94a\r\n" \
"Content-Type: application/json; charset=UTF-8\r\n" \
"\r\n" \
"{\"directive\":{\"header\":{\"namespace\":\"SpeechSynthesizer\",\"name\":\"Speak\",\"messageId\":\"019a5d54-d571-4e0a-a9bd-695d97eec2ad\",\"dialogRequestId\":\"dialog-request-id-4\"},\"payload\":{\"url\":\"cid:WhatsUpActioncf5a4f75-be62-4305-a10b-f53085f261af_1668927456\",\"format\":\"AUDIO_MPEG\",\"token\":\"amzn1.as-ct.v1.Domain:Application:Zeitgeist:Knight:WhatsUp#ACRI#WhatsUpActioncf5a4f75-be62-4305-a10b-f53085f261af\"}}}\r\n" \
"--854873ff-ac23-4ebd-b329-00bd8cccd94a\r\n" \
"Content-Type: application/json; charset=UTF-8\r\n" \
"\r\n" \
"{\"directive\":{\"header\":{\"namespace\":\"SpeechSynthesizer\",\"name\":\"Speak\",\"messageId\":\"d96dc0a1-685c-4145-882e-f8b585c841e0\",\"dialogRequestId\":\"dialog-request-id-4\"},\"payload\":{\"url\":\"cid:WhatsUpActionb00cf3ba-778f-47c7-9e30-16cca1bd2235_1731975007\",\"format\":\"AUDIO_MPEG\",\"token\":\"amzn1.as-ct.v1.Domain:Application:Zeitgeist:Knight:WhatsUp#ACRI#WhatsUpActionb00cf3ba-778f-47c7-9e30-16cca1bd2235\"}}}\r\n" \
"--854873ff-ac23-4ebd-b329-00bd8cccd94a\r\n" \
"Content-Type: application/json; charset=UTF-8\r\n" \
"\r\n" \
"{\"directive\":{\"header\":{\"namespace\":\"SpeechSynthesizer\",\"name\":\"Speak\",\"mess"

#define MSG55 \
"ageId\":\"c6f5e385-2e4d-4e2c-afd4-540d6bbbb13a\",\"dialogRequestId\":\"dialog-request-id-4\"},\"payload\":{\"url\":\"cid:WhatsUpAction4034783b-d206-4bc0-8ec3-936da620dc65_1359737806\",\"format\":\"AUDIO_MPEG\",\"token\":\"amzn1.as-ct.v1.Domain:Application:Zeitgeist:Knight:WhatsUp#ACRI#WhatsUpAction4034783b-d206-4bc0-8ec3-936da620dc65\"}}}\r\n" \
"--854873ff-ac23-4ebd-b329-00bd8cccd94a\r\n" \
"Content-Type: application/json; charset=UTF-8\r\n" \
"\r\n" \



#define BOUNDARY6 "--854873ff-ac23-4ebd-b329-00bd8cccd94a"
#define MSG6 \
"--854873ff-ac23-4ebd-b329-00bd8cccd94a\r\n" \
"Content-Type: application/json; charset=UTF-8\r\n" \
"\r\n" \
"{\"directive\":{\"header\":{\"namespace\":\"SpeechSynthesizer\",\"name\":\"Speak\",\"messageId\":\"019a5d54-d571-4e0a-a9bd-695d97eec2ad\",\"dialogRequestId\":\"dialog-request-id-4\"},\"payload\":{\"url\":\"cid:WhatsUpActioncf5a4f75-be62-4305-a10b-f53085f261af_1668927456\",\"format\":\"AUDIO_MPEG\",\"token\":\"amzn1.as-ct.v1.Domain:Application:Zeitgeist:Knight:WhatsUp#ACRI#WhatsUpActioncf5a4f75-be62-4305-a10b-f53085f261af\"}}}\r\n" \
"--854873ff-ac23-4ebd-b329-00bd8cccd94a\r\n" \
"Content-Type: application/json; charset=UTF-8\r\n" \
"\r\n" \
"{\"directive\":{\"header\":{\"namespace\":\"SpeechSynthesizer\",\"name\":\"Speak\",\"messageId\":\"d96dc0a1-685c-4145-882e-f8b585c841e0\",\"dialogRequestId\":\"dialog-request-id-4\"},\"payload\":{\"url\":\"cid:WhatsUpActionb00cf3ba-778f-47c7-9e30-16cca1bd2235_1731975007\",\"format\":\"AUDIO_MPEG\",\"token\":\"amzn1.as-ct.v1.Domain:Application:Zeitgeist:Knight:WhatsUp#ACRI#WhatsUpActionb00cf3ba-778f-47c7-9e30-16cca1bd2235\"}}}\r\n" \
"--854873ff-ac23-4ebd-b329-00bd8cccd94a\r\n" \
"Content-Type: application/json; charset=UTF-8\r\n" \
"\r\n" \
"{\"directive\":{\"header\":{\"namespace\":\"SpeechSynthesizer\",\"name\":\"Speak\",\"mess"



#define BOUNDARY7 "--854873ff-ac23-4ebd-b329-00bd8cccd94a"
#define MSG7 \
"--854873ff-ac23-4ebd-b329-00bd8cccd94a\r\n" \
"Content-Type: application/json; charset=UTF-8\r\n" \
"\r\n" \
"{\"directive\":{\"header\":{\"namespace\":\"SpeechSynthesizer\",\"name\":\"Speak\",\"messageId\":\"019a5d54-d571-4e0a-a9bd-695d97eec2ad\",\"dialogRequestId\":\"dialog-request-id-4\"},\"payload\":{\"url\":\"cid:WhatsUpActioncf5a4f75-be62-4305-a10b-f53085f261af_1668927456WhatsUpActioncf5a4f75-be62-4305-a10b-f53085f261af_1668927456WhatsUpActioncf5a4f75-be62-4305-a10b-f53085f261af_1668927456WhatsUpActioncf5a4f75-be62-4305-a10b-f53085f261af_1668927456WhatsUpActioncf5a4f75-be62-4305-a10b-f53085f261af_1668927456WhatsUpActioncf5a4f75-be62-4305-a10b-f53085f261af_1668927456WhatsUpActioncf5a4f75-be62-4305-a10b-f53085f261af_1668927456WhatsUpActioncf5a4f75-be62-4305-a10b-f53085f261af_1668927456WhatsUpActioncf5a4f75-be62-4305-a10b-f53085f261af_1668927456WhatsUpActioncf5a4f75-be62-4305-a10b-f53085f261af_1668927456WhatsUpActioncf5a4f75-be62-4305-a10b-f53085f261af_1668927456WhatsUpActioncf5a4f75-be62-4305-a10b-f53085f261af_1668927456WhatsUpActioncf5a4f75-be62-4305-a10b-f53085f261af_1668927456WhatsUpActioncf5a4f75-be62-4305-a10b-f53085f261af_1668927456WhatsUpActioncf5a4f75-be62-4305-a10b-f53085f261af_1668927456WhatsUpActioncf5a4f75-be62-4305-a10b-f53085f261af_1668927456WhatsUpActioncf5a4f75-be62-4305-a10b-f53085f261af_1668927456WhatsUpActioncf5a4f75-be62-4305-a10b-f53085f261af_1668927456WhatsUpActioncf5a4f75-be62-4305-a10b-f53085f261af_1668927456WhatsUpActioncf5a4f75-be62-4305-a10b-f53085f261af_1668927456\",\"format\":\"AUDIO_MPEG\",\"token\":\"amzn1.as-ct.v1.Domain:Application:Zeitgeist:Knight:WhatsUp#ACRI#WhatsUpActioncf5a4f75-be62-4305-a10b-f530"


#define MSG77 \
"85f261af\"}}}\r\n" \


char msg[]=MSG7;
char boundary[]=BOUNDARY7;

void multipart_parser_chk()
{
#if 1
    printf("\n\n------------MSG, len=%d----------\n%s\n-----------------\n\n",strlen(msg),msg);
    //check_for_complete_multipart_data(msg, boundary, strlen(msg),0,0,0,0);
#endif

    int type;

    type = extract_multipart_body(msg, strlen(msg), boundary,
                                  0,MSG77,
                                  0,
                                  0,0,0);


}

#endif

