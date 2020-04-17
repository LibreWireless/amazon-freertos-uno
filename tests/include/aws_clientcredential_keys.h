/*
 * FreeRTOS V202002.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

#ifndef AWS_CLIENT_CREDENTIAL_KEYS_H
#define AWS_CLIENT_CREDENTIAL_KEYS_H

/*
 * @brief PEM-encoded client certificate.
 *
 * @todo If you are running one of the FreeRTOS demo projects, set this
 * to the certificate that will be used for TLS client authentication.
 *
 * @note Must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----\n"
 */
#define keyCLIENT_CERTIFICATE_PEM                   \
"-----BEGIN CERTIFICATE-----\n"\
"MIIDuTCCAqECFGh2ifOAVNjjMU59lAk7hzju85MTMA0GCSqGSIb3DQEBCwUAMIGY\n"\
"MQswCQYDVQQGEwJVUzELMAkGA1UECAwCV0ExDjAMBgNVBAcMBVBsYWNlMRYwFAYD\n"\
"VQQKDA1MaWJyZXdpcmVsZXNzMQswCQYDVQQLDAJJVDEeMBwGA1UEAwwVd3d3Lmxp\n"\
"YnJld2lyZWxlc3MuY29tMScwJQYJKoZIhvcNAQkBFhhzYWNoaW5AbGlicmV3aXJl\n"\
"bGVzcy5jb20wHhcNMjAwMjIxMTQyOTE1WhcNMjEwMjIwMTQyOTE1WjCBmDELMAkG\n"\
"A1UEBhMCVVMxCzAJBgNVBAgMAldBMQ4wDAYDVQQHDAVQbGFjZTEWMBQGA1UECgwN\n"\
"TGlicmV3aXJlbGVzczELMAkGA1UECwwCSVQxHjAcBgNVBAMMFXd3dy5saWJyZXdp\n"\
"cmVsZXNzLmNvbTEnMCUGCSqGSIb3DQEJARYYc2FjaGluQGxpYnJld2lyZWxlc3Mu\n"\
"Y29tMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAncJCX0ExqabAbeN6\n"\
"Axh013KkvNYBWqeod1LgN5ng4MUrgwpzGZvN9NBtbWrF0L3DfDcZ0R/RzFdEmuKJ\n"\
"TKBYksAO1uXI7g1kUSo99w5ECm2WyzX6ExN9hyjTLjolukNzwa2lMIQAdCcpDtN9\n"\
"FEXkDmsciwn/Qr/vfOkz/OlbemrVsBLISGRtOoDYCpm3MvSDm9Aev7fCZ1O3ny8F\n"\
"ms3tAhRi0OHdPLUQmrlPzJfd8In+E2oZO4tduKd5mgKTZV24RSdi8MBX5rRN6EDf\n"\
"AU+t7MpoCpKazt88B+uNfnyvDW1qrRk3YnJWgOeqZWEHvS0NUDWAiSAa43rDxNdQ\n"\
"AmUN/QIDAQABMA0GCSqGSIb3DQEBCwUAA4IBAQDLN1hDQ8WCpFIpi7CDUI/INqPL\n"\
"NxstLCaVlHayDcJUlowHArkt/UzTKHicrAosVtUZT6hfh+SK4DXbx8gfqBWt82BU\n"\
"bI4YeJCotvYqPLTERMh2B3q1oICD+7D7aQN81M3WeIr9qHUA7yDcS+NlCjehSMns\n"\
"oQe2FdCL+udrmYdTPtjnXFd73QN5mbFF3dIqa7NVRu7olE4qPtilY0P0Cn3u2Hq5\n"\
"OQUbbaPW76c74MsCW7ykkzcZwLGGAfcmQrFIefwOhc973lDPvbqJgYAIyG5I0obg\n"\
"XJ6kYxXyEL/UMOk5nVxRpxfHgnCaOaz3uh5sd/UlN9bU1WWAkkYsBgPvotlf\n"\
"-----END CERTIFICATE-----"

/*
 * @brief PEM-encoded issuer certificate for AWS IoT Just In Time Registration (JITR).
 *
 * @todo If you are using AWS IoT Just in Time Registration (JITR), set this to
 * the issuer (Certificate Authority) certificate of the client certificate above.
 *
 * @note This setting is required by JITR because the issuer is used by the AWS
 * IoT gateway for routing the device's initial request. (The device client
 * certificate must always be sent as well.) For more information about JITR, see:
 *  https://docs.aws.amazon.com/iot/latest/developerguide/jit-provisioning.html,
 *  https://aws.amazon.com/blogs/iot/just-in-time-registration-of-device-certificates-on-aws-iot/.
 *
 * If you're not using JITR, set below to NULL.
 *
 * Must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----\n"
 */
#define keyJITR_DEVICE_CERTIFICATE_AUTHORITY_PEM    ""

/*
 * @brief PEM-encoded client private key.
 *
 * @todo If you are running one of the FreeRTOS demo projects, set this
 * to the private key that will be used for TLS client authentication.
 *
 * @note Must include the PEM header and footer:
 * "-----BEGIN RSA PRIVATE KEY-----\n"\
 * "...base64 data...\n"\
 * "-----END RSA PRIVATE KEY-----\n"
 */
#define keyCLIENT_PRIVATE_KEY_PEM                   \
"-----BEGIN RSA PRIVATE KEY-----\n"\
"MIIEowIBAAKCAQEAncJCX0ExqabAbeN6Axh013KkvNYBWqeod1LgN5ng4MUrgwpz\n"\
"GZvN9NBtbWrF0L3DfDcZ0R/RzFdEmuKJTKBYksAO1uXI7g1kUSo99w5ECm2WyzX6\n"\
"ExN9hyjTLjolukNzwa2lMIQAdCcpDtN9FEXkDmsciwn/Qr/vfOkz/OlbemrVsBLI\n"\
"SGRtOoDYCpm3MvSDm9Aev7fCZ1O3ny8Fms3tAhRi0OHdPLUQmrlPzJfd8In+E2oZ\n"\
"O4tduKd5mgKTZV24RSdi8MBX5rRN6EDfAU+t7MpoCpKazt88B+uNfnyvDW1qrRk3\n"\
"YnJWgOeqZWEHvS0NUDWAiSAa43rDxNdQAmUN/QIDAQABAoIBABZ2GSMc0ihYgJ9k\n"\
"uvOD4OboAMKOKcUxh8/tcdUYyKbYC9jtfPPRdiJ8JohkomOVESc3ZSqcQC+64R64\n"\
"UFojnljOlY5NSy1xpK3VuNrbIh7l+YlXVxKuPLoouuCjEMoTXoDd614b/UCMbtEY\n"\
"lX90cAMJhxfYxYpIb522SluhEhA8uo3X0kvi5gXPFThHIbSLYSLxT6c/qPXGiEE+\n"\
"8TkCDRFDK2TU+sgLqco0cXsKA7gWFm0hfUC/Oxs8uenia23q1VSwMrMHqfNSqyBu\n"\
"goN+wfVMNkftjXmY9xq2WogvB4yM4srAXHhKSYXOYLAe1I6ZomuU7nlJzw46Dtxz\n"\
"F1v5WqECgYEAzu3ITV3Ed6752SFfkVB2H7oS2G0BTlsHBoMlVZMYE2Z2OmNOir09\n"\
"wzbM0BOOSrtkICpWcrbgjDIYt6d7ei6GuvqihFJdG6ATtGZk6BbirzDGy5/awr+n\n"\
"yKn6Bdbr44AfR0n8u1ybU8CUDwOgkKvZ6yBMDdE8YF5Ut1FMCSIVqPkCgYEAwyt3\n"\
"07umaLMWGSEhgu1bFuqkwi2/o3HMEt44bLt8ujaRDZ+iiDc+Z95/ud9n7p6kd6AL\n"\
"xBZPBgYxHcjRFU8j8GHTGtVNq/dEYHdch0fkDWkujxtaHQ4wfX/eWIh+SJY1thgn\n"\
"Sbc+eZJR8oDLZKyTmzLrjyKpFvL4M51+f0gbMiUCgYBCaQvU0JgiNRTYe555O5J9\n"\
"gjFUJj+6DvrFO0e7HBco+sRM3twxKKTuxuKakPwkvdlXfV77N/f+5oEKSAUX5GC3\n"\
"F4Ma5ngdSpWoWwhdeCLOSOA0L5x8zheiDfNA9oYEIHVpYrRqyUDMc0zROL/KTm0E\n"\
"yfu+n306DGwx3TSC5d5/uQKBgFVzdLV5lXSF5IkAHoIKljVEavqxuRRAwM8KCL5i\n"\
"oEuPlJbYa/sj5OjpXBbvn7u0LeJKapxiABttHpgh0pl32w5mZl17QtSmIIPz/skk\n"\
"Ss8sXDxAB4ZtLgHkuF8e89uoGMAvdxQpbOshi0uX5HWhscbj1osG6+2mV9GRhU8J\n"\
"LQ8ZAoGBAMSTk5wxvUFu3s0DReX5XFsF8ADfqt/tuwl5bfMRezKpGYmC7AEx+uZc\n"\
"K3XAMYMsxhbvhPB0I/RtRkg5kdlb8dkhU6LAh0wf3hLeqoyRjPTl7fZa0oLhZK74\n"\
"5e9TcTheD3WMCRsHppBpA5cHUX+wPSR5BIBthbIutyv/rtRFXL7h\n"\
"-----END RSA PRIVATE KEY-----"

#endif /* AWS_CLIENT_CREDENTIAL_KEYS_H */
