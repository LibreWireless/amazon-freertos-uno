"""
FreeRTOS
Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

http://aws.amazon.com/freertos
http://www.FreeRTOS.org

"""

from .aws_ota_test_case import OtaTestCase
from .aws_ota_test_result import OtaTestResult


class OtaTestDummyTest(OtaTestCase):
    """This test is for debugging code changes without waiting for projects to build.
    """
    is_positive = False

    def setup(self):
        print('Ran OtaTestDummyTest::setup.')
        # Adding empty list for return to indicate the successful setup.
        return []

    def teardown(self):
        print('Ran OtaTestDummyTest::teardown.')

    def run(self):
        print('Ran OtaTestDummyTest::run.')
        return OtaTestResult(testName=self._name, result=OtaTestResult.PASS)
