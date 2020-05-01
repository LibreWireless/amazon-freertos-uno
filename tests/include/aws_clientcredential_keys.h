#ifndef AWS_CLIENT_CREDENTIAL_KEYS_H
#define AWS_CLIENT_CREDENTIAL_KEYS_H

#include <stdint.h>

/*
 * PEM-encoded client certificate.
 *
 * Must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----"
 */
#define keyCLIENT_CERTIFICATE_PEM \
"-----BEGIN CERTIFICATE-----\n"\
"MIIDWjCCAkKgAwIBAgIVAOgL+dxgKNsOuPdlmwq2vCZJ/ilEMA0GCSqGSIb3DQEB\n"\
"CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\n"\
"IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMDA0MjIxMzUx\n"\
"MDdaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\n"\
"dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDQzOxKXmqyZBlPrHAj\n"\
"oa4APn3/E8cXqIUQTuX+5zJExtvnS2qUY/dtqPiz9gN9lkq/1Qw2FYjmTctXbbqc\n"\
"69F9f30VqT0gU56F0/m752skTtQnpB7QVRKpB5TjQ+fG3+L9ZVyfOwD/umwkpjvx\n"\
"2QB5IbUvfyRm9zQIUo56JQTYTLyqWv4MAIHHf5qLeZXU9QEx9ISRtRPfiazefWwv\n"\
"UmdEDhYKUOZj/GQ99xb+1TFNS9QfEIXhSY8zYgU4FEGl65GbIB4bsNoAZZ3/MM1z\n"\
"CMuNzCtRVkSNJjY8lsQ/NfKA/LL3/Ic79iCPC3f2x37BbGwIuCtaGfN0kStEyXRc\n"\
"2zRJAgMBAAGjYDBeMB8GA1UdIwQYMBaAFIR9s7lNKD4R8MwYSubUzo6M8zHLMB0G\n"\
"A1UdDgQWBBROzEaVF125hBPZ4XU/iT5tNdz1kjAMBgNVHRMBAf8EAjAAMA4GA1Ud\n"\
"DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEANTm8yW64+w7TZ3DmMblSJ8EK\n"\
"cojGJW6Hk5W0M4lhjocjcVbuDHmcbXlOye2zj5mo2vC+aX7x/qBD5yqYcyR1BfGM\n"\
"vY8CSWGmcSZ5qBjR6HkplCJZ5AAKXgwDVHisTf/mc73O+NMtkSYu3srregTJifBW\n"\
"ajovqgFpzicdTGwipmm+Bm9t2DW7vqbqtgQw2xgylg4zzYvHRR7o6qu5YNDq3T2s\n"\
"5gqwFSduHUKsnVf8+/HPfkeswZJv59lfz9SIK5VGLcPL4jMXkqai99iqmVLUiPDa\n"\
"z3+ckzApFQ1NsT+5D1qGEBYyAUvo61tL31dYjpApwmz5XZ1LdBqialn9bzWw1A==\n"\
"-----END CERTIFICATE-----"

/*
 * PEM-encoded client private key.
 *
 * Must include the PEM header and footer:
 * "-----BEGIN RSA PRIVATE KEY-----\n"\
 * "...base64 data...\n"\
 * "-----END RSA PRIVATE KEY-----"
 */
#define keyCLIENT_PRIVATE_KEY_PEM \
"-----BEGIN RSA PRIVATE KEY-----\n"\
"MIIEogIBAAKCAQEA0MzsSl5qsmQZT6xwI6GuAD59/xPHF6iFEE7l/ucyRMbb50tq\n"\
"lGP3baj4s/YDfZZKv9UMNhWI5k3LV226nOvRfX99Fak9IFOehdP5u+drJE7UJ6Qe\n"\
"0FUSqQeU40Pnxt/i/WVcnzsA/7psJKY78dkAeSG1L38kZvc0CFKOeiUE2Ey8qlr+\n"\
"DACBx3+ai3mV1PUBMfSEkbUT34ms3n1sL1JnRA4WClDmY/xkPfcW/tUxTUvUHxCF\n"\
"4UmPM2IFOBRBpeuRmyAeG7DaAGWd/zDNcwjLjcwrUVZEjSY2PJbEPzXygPyy9/yH\n"\
"O/Ygjwt39sd+wWxsCLgrWhnzdJErRMl0XNs0SQIDAQABAoIBAA5Qjj6G/I+gVy/k\n"\
"JYf71J8FqcOsCnEvx3eXwSLZnNOkQn036WWk+NiWxf4odpLMk/FU3NJ0ZX9MhA1J\n"\
"Y4rQi/srm1q50Iv/z5VjM/LS6cCCev8AvHAR9QaLk4SFKkWzIa+3nEL6W5YspK9a\n"\
"ii+JbgPf8LkB4XABsJqFdmkfUpa1hFyu3CGh6uRqMoxkhtAEKv+kiFhl6NLgGGEG\n"\
"krQZlKUjI31sqMJ8IkIvkI5nVHOuWgXYouTu9T8EQdlmjnxUanBBPXVWL9Snjqcy\n"\
"7up0bq1WlEYjqDZhp/2IBQUZuQPXVqwXO6eIjQjcnfdRByYLEAO46Vrws4KYKnqk\n"\
"97eU9bUCgYEA7++haZKG5AmapfAqI9yuwhEdaw8SwqrtIMft2qgR+RyYLU/LB9Z2\n"\
"3YLblxI6t7lf8EHWSddUXCRdXvwFZMNBSagPgLchaqoDyJw09B15Djuj4h31DEKR\n"\
"wA2sHIaKC5cTXtM8urB0c7bHytJGxwLmKOU48D6Hxv1zpkf5WCtN+sMCgYEA3sel\n"\
"a6aKn2AMGeSxb1FjaxGY0utJiJmUjk2pKrPZUMUSnldCdFaohm2DnMG0sVuyIbsA\n"\
"33mVzxCHIrFom+Fq0kCvxPWWmsNqP6njK9DItaRcf9ux/nT6i0+tmc/gQf0XvHHm\n"\
"9QMly4g7FSFej8yHZgVqxYO5AbcemQ3wDc3NbAMCgYAVdwOitTgaGH3cUIMEmE6O\n"\
"EAfotv1/qtjx8NDnmdeZyKQYkaXhOp+Bq55Hgpr8KrpZfRpVmszyPVKZF8THwewK\n"\
"Ud2pLzjvGOyjus3F9QkKa+16YiG1ChON8esu1h5tcQOLnSw2q2iPnY98JpmsXicH\n"\
"C5Kvc3ikJbJ98rxs1drxDwKBgCGpy15D8Sh6C/oRq5olkz9Hjm84rIjepCsIoypX\n"\
"uNvSm6ifiOQpgBeoDr4uKw6ty3H7Xvtl1PRQDAt7AVKksk6JBcZeUd6a7sAl/LTP\n"\
"PLTt3ChZ20CXDpDkflgCqGFwTBjmoT6etiRWNo9P1okmH8OTx/mGmPsgX5hDGeYM\n"\
"FiFfAoGAUcTP1vL/l+2RSr1Nytzgx6WCjk8L278t3ET233lwf7fgdhNPo83QVCib\n"\
"7bK1xy+0hDhDceBczNeU4f1dF8g1mlfyAYpXyZJDK9CRcSGRpH7mNs0sDQAydWy1\n"\
"BC7YhF7F6kMlsp5mhsqYc3iuUKE2Y3IVdiSr6brPemxAQ9Nva9Q=\n"\
"-----END RSA PRIVATE KEY-----"

/*
 * PEM-encoded Just-in-Time Registration (JITR) certificate (optional).
 *
 * If used, must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----"
 */
#define keyJITR_DEVICE_CERTIFICATE_AUTHORITY_PEM  ""


#endif /* AWS_CLIENT_CREDENTIAL_KEYS_H */
