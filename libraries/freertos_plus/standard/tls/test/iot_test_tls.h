/*
 * Amazon FreeRTOS TLS V1.1.6
 * Copyright (C) 2018 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
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

#ifndef _AWS_TLS_TEST_H_
#define _AWS_TLS_TEST_H_

/*
 * PEM-encoded client certificate.
 *
 * Certificate for P-256 elliptic curve key.
 */
static const char tlstestCLIENT_CERTIFICATE_PEM_EC[] = "-----BEGIN CERTIFICATE-----\n"\
"MIIDCTCCAfGgAwIBAgIUckMgNw6LhKuqURPow7lW0I4y1BowDQYJKoZIhvcNAQEL\n"\
"BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g\n"\
"SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIwMDIxODE0MzM1\n"\
"MFoXDTQ5MTIzMTIzNTk1OVowgZgxCzAJBgNVBAYTAlVTMQswCQYDVQQIDAJXQTEO\n"\
"MAwGA1UEBwwFUGxhY2UxFjAUBgNVBAoMDUxpYnJlV2lyZWxlc3MxCzAJBgNVBAsM\n"\
"AklUMR4wHAYDVQQDDBV3d3cubGlicmV3aXJlbGVzcy5jb20xJzAlBgkqhkiG9w0B\n"\
"CQEWGHNhY2hpbkBsaWJyZXdpcmVsZXNzLmNvbTBZMBMGByqGSM49AgEGCCqGSM49\n"\
"AwEHA0IABInMRztZJ3BfX5fFfuzTTeYNzjMHkHLdM1zd0qNYsPdbvC7OwCd4pSIL\n"\
"qEvfu2p/FUPFhEXN0IB8V79ilnwjOiejYDBeMB8GA1UdIwQYMBaAFAWcZen79hqV\n"\
"CGseqR620F3GwruYMB0GA1UdDgQWBBRg+hwZm2L107P8ZwWKAg9cwPDCyDAMBgNV\n"\
"HRMBAf8EAjAAMA4GA1UdDwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEABTfA\n"\
"eyOZstV9PgkL6ftx6MDEZGzuuwfU84kTkjQkhCu6ea04ycupCeGYl2oM9EjIZkM/\n"\
"zyu4HQH8U3hk+w8Fy9Pw1yRChdqEuXH1lJx1mNFdTXcAv+7DkSEvfR0w5toXZ67Q\n"\
"OXBzHiYiqEBz4XtE6zGlAZ2GLeV6K4LxemTQmpwG55j1vGcK67b9azAM3OML4Q5W\n"\
"F4s0OkfBaG99bLh0f/BC1+agQ+glSjMv1Kl9+W0s7RURqCW6Bv+dSsMZpej1BgMx\n"\
"WtTUerLxyWN9eRcivGiUcwQ+j6bdQgthkWVq49IAkUovk1JJv1UERsINq3YyOQFT\n"\
"rCQaRjaqaNYjP3axJA==\n"\
"-----END CERTIFICATE-----";

/*
 * PEM-encoded client private key.
 *
 * This is a P-256 elliptic curve key.
 */
static const char tlstestCLIENT_PRIVATE_KEY_PEM_EC[] = "-----BEGIN EC PRIVATE KEY-----\n"\
"MHcCAQEEIMuh6eW5OePM2z+QxsUgfkyDidgbu0p4lFNASREefIXqoAoGCCqGSM49\n"\
"AwEHoUQDQgAEicxHO1kncF9fl8V+7NNN5g3OMweQct0zXN3So1iw91u8Ls7AJ3il\n"\
"IguoS9+7an8VQ8WERc3QgHxXv2KWfCM6Jw==\n"\
"-----END EC PRIVATE KEY-----";

/* One character of this certificate has been changed in the issuer
 * name from Amazon Web Services to Amazon Web Cervices. */
static const char tlstestCLIENT_CERTIFICATE_PEM_MALFORMED[] = "-----BEGIN CERTIFICATE-----\n"\
"MIIDWTCCAkGgAwIBAgIUA9dyQpWBVhzazH25noeaukl95pUwDQYJKoZIhvcNAQEL\n"\
"BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBDZXJ2aWNlcyBPPUFtYXpvbi5jb20g\n"\
"SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIwMDIxNzEwMjU1\n"\
"M1oXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0\n"\
"ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAMLTSf6XUyV+DfQvTJzP\n"\
"2+bBoLKYiURgvMongSIQVXbc1ed/QNRFwfYr9MOEnDSkE5eM2QAdJNDkedRnx0Ww\n"\
"qBoShChPHHWttB+Fi9bu5/2YGrUqOzOUVDZice9HhJY935cyzim8mJYw0phWIaWz\n"\
"5S+bP23SjxhzlQdUPDbewX1rnRLhIqSAa/XIvfTFqIduqhmfjv76VznQkyUwj9Tt\n"\
"MJipRNd8VX4LnITh519vheUWnR3raAoTpZzsjeMnAmJVLoC2sLPE/8rpnqKVzVDa\n"\
"BTpFBxdJIwQkzKfj2lZl1PQJb54GUwAOn6bgQPe1kgx5RuCE/DVpdAVraxvQV6GY\n"\
"L4sCAwEAAaNgMF4wHwYDVR0jBBgwFoAUBKjfetBCWk4QFbSAvPI4a0V8SvMwHQYD\n"\
"VR0OBBYEFJIAWAkGkAExOvVEyNoQDGGdVm7VMAwGA1UdEwEB/wQCMAAwDgYDVR0P\n"\
"AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQAM4b4cPX/VNFU39IdxLrUyDYsR\n"\
"sonad++4IscQnvhs9BjdkQWx0ybOBRPTlbwQbcnd4xmYCRdp50pwJ2LqKv62ZdK7\n"\
"+iQta5jIL66ToA94D6jDyLEpSeYHFlN9voL3gbmxtrnITsCiUjdd0rPNbqa2AA6P\n"\
"n9cCaY/BQ8ZiJfFlbJiIQS7kcr9df7kH+QKW4ismUdPocunXdOIuFVLLyslMNrEL\n"\
"MaIE9pJ0mqJpqExV5uDSDGq+S+Xsg1tEIT0Rm+OptX7zpsJhqqFevsmK39owM1ZZ\n"\
"pt/ZqW/34GSwMUf1MvLaZF24opddJSeU4z7cdRbwdL5xrdZv6IQRyCsTH5gL\n"\
"-----END CERTIFICATE-----";

/* Certificate which is not trusted by the broker. */
static const char tlstestCLIENT_UNTRUSTED_CERTIFICATE_PEM[] = "-----BEGIN CERTIFICATE-----\n"\
"MIIDWTCCAkGgAwIBAgIUA9dyQpWBVhzazH25noeaukl95pUwDQYJKoZIhvcNAQEL\n"\
"BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBDZXJ2aWNlcyBPPUFtYXpvbi5jb20g\n"\
"SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIwMDIxNzEwMjU1\n"\
"M1oXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0\n"\
"ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAMLTSf6XUyV+DfQvTJzP\n"\
"2+bBoLKYiURgvMongSIQVXbc1ed/QNRFwfYr9MOEnDSkE5eM2QAdJNDkedRnx0Ww\n"\
"qBoShChPHHWttB+Fi9bu5/2YGrUqOzOUVDZice9HhJY935cyzim8mJYw0phWIaWz\n"\
"5S+bP23SjxhzlQdUPDbewX1rnRLhIqSAa/XIvfTFqIduqhmfjv76VznQkyUwj9Tt\n"\
"MJipRNd8VX4LnITh519vheUWnR3raAoTpZzsjeMnAmJVLoC2sLPE/8rpnqKVzVDa\n"\
"BTpFBxdJIwQkzKfj2lZl1PQJb54GUwAOn6bgQPe1kgx5RuCE/DVpdAVraxvQV6GY\n"\
"L4sCAwEAAaNgMF4wHwYDVR0jBBgwFoAUBKjfetBCWk4QFbSAvPI4a0V8SvMwHQYD\n"\
"VR0OBBYEFJIAWAkGkAExOvVEyNoQDGGdVm7VMAwGA1UdEwEB/wQCMAAwDgYDVR0P\n"\
"AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQAM4b4cPX/VNFU39IdxLrUyDYsR\n"\
"sonad++4IscQnvhs9BjdkQWx0ybOBRPTlbwQbcnd4xmYCRdp50pwJ2LqKv62ZdK7\n"\
"+iQta5jIL66ToA94D6jDyLEpSeYHFlN9voL3gbmxtrnITsCiUjdd0rPNbqa2AA6P\n"\
"n9cCaY/BQ8ZiJfFlbJiIQS7kcr9df7kH+QKW4ismUdPocunXdOIuFVLLyslMNrEL\n"\
"MaIE9pJ0mqJpqExV5uDSDGq+S+Xsg1tEIT0Rm+OptX7zpsJhqqFevsmK39owM1ZZ\n"\
"pt/ZqW/34GSwMUf1MvLaZF24opddJSeU4z7cdRbwdL5xrdZv6IQRyCsTH5gL\n"\
"-----END CERTIFICATE-----";

/* Private key corresponding to the untrusted certificate. */
static const char tlstestCLIENT_UNTRUSTED_PRIVATE_KEY_PEM[] = "-----BEGIN EC PRIVATE KEY-----\n"\
"MHcCAQEEIFMo04l9SqJGT54GeJZQqxGHPE8+8Ci0KlCQYvWV7mukoAoGCCqGSM49\n"\
"AwEHoUQDQgAEtB2Af0E/zr/leyqR59loFBi9NqZ3+iCAT6XayF6R82zLO7ubxzil\n"\
"01+P7ofqLTcapaDipZkcWAu64MzacPurNQ==\n"\
"-----END EC PRIVATE KEY-----";

/* Device certificate created using BYOC instructions. */
static const char tlstestCLIENT_BYOC_CERTIFICATE_PEM[] = "-----BEGIN CERTIFICATE-----\n"\
"MIIDWTCCAkGgAwIBAgIUA9dyQpWBVhzazH25noeaukl95pUwDQYJKoZIhvcNAQEL\n"\
"BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBDZXJ2aWNlcyBPPUFtYXpvbi5jb20g\n"\
"SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIwMDIxNzEwMjU1\n"\
"M1oXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0\n"\
"ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAMLTSf6XUyV+DfQvTJzP\n"\
"2+bBoLKYiURgvMongSIQVXbc1ed/QNRFwfYr9MOEnDSkE5eM2QAdJNDkedRnx0Ww\n"\
"qBoShChPHHWttB+Fi9bu5/2YGrUqOzOUVDZice9HhJY935cyzim8mJYw0phWIaWz\n"\
"5S+bP23SjxhzlQdUPDbewX1rnRLhIqSAa/XIvfTFqIduqhmfjv76VznQkyUwj9Tt\n"\
"MJipRNd8VX4LnITh519vheUWnR3raAoTpZzsjeMnAmJVLoC2sLPE/8rpnqKVzVDa\n"\
"BTpFBxdJIwQkzKfj2lZl1PQJb54GUwAOn6bgQPe1kgx5RuCE/DVpdAVraxvQV6GY\n"\
"L4sCAwEAAaNgMF4wHwYDVR0jBBgwFoAUBKjfetBCWk4QFbSAvPI4a0V8SvMwHQYD\n"\
"VR0OBBYEFJIAWAkGkAExOvVEyNoQDGGdVm7VMAwGA1UdEwEB/wQCMAAwDgYDVR0P\n"\
"AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQAM4b4cPX/VNFU39IdxLrUyDYsR\n"\
"sonad++4IscQnvhs9BjdkQWx0ybOBRPTlbwQbcnd4xmYCRdp50pwJ2LqKv62ZdK7\n"\
"+iQta5jIL66ToA94D6jDyLEpSeYHFlN9voL3gbmxtrnITsCiUjdd0rPNbqa2AA6P\n"\
"n9cCaY/BQ8ZiJfFlbJiIQS7kcr9df7kH+QKW4ismUdPocunXdOIuFVLLyslMNrEL\n"\
"MaIE9pJ0mqJpqExV5uDSDGq+S+Xsg1tEIT0Rm+OptX7zpsJhqqFevsmK39owM1ZZ\n"\
"pt/ZqW/34GSwMUf1MvLaZF24opddJSeU4z7cdRbwdL5xrdZv6IQRyCsTH5gL\n"\
"-----END CERTIFICATE-----";

/* Device private key created using BYOC instructions. */
static const char tlstestCLIENT_BYOC_PRIVATE_KEY_PEM[] = "-----BEGIN EC PRIVATE KEY-----\n"\
"MHcCAQEEIFMo04l9SqJGT54GeJZQqxGHPE8+8Ci0KlCQYvWV7mukoAoGCCqGSM49\n"\
"AwEHoUQDQgAEtB2Af0E/zr/leyqR59loFBi9NqZ3+iCAT6XayF6R82zLO7ubxzil\n"\
"01+P7ofqLTcapaDipZkcWAu64MzacPurNQ==\n"\
"-----END EC PRIVATE KEY-----";

#endif /* ifndef _AWS_TLS_TEST_H_ */
