#include <Arduino.h>
#include <unity.h>

#include <TPMS.h>

void setUp(void)
{
  // set stuff up here
}

void tearDown(void)
{
  // clean stuff up here
}

void test_invalid_data()
{
  const TPMS::Data empty;
  TEST_ASSERT_EQUAL(0, empty.address.compare(""));
  TEST_ASSERT_EQUAL(0, empty.alarmFlags);
  TEST_ASSERT_EQUAL(0, empty.battery);
  TEST_ASSERT_EQUAL(0, empty.manufacturer.compare(""));
  TEST_ASSERT_EQUAL_FLOAT(0.0f, empty.pressureBar);
  TEST_ASSERT_EQUAL_FLOAT(0.0f, empty.pressureKPa);
  TEST_ASSERT_EQUAL_FLOAT(0.0f, empty.pressurePsi);
  TEST_ASSERT_EQUAL_FLOAT(0.0f, empty.temperatureC);
  TEST_ASSERT_EQUAL_FLOAT(0.0f, empty.temperatureF);
}

void test_normal_data()
{
  const TPMS::Data fromData("000180eaca124d01971300007f0a00006301");
  TEST_ASSERT_EQUAL(0, fromData.address.compare("80eaca124d01"));
  TEST_ASSERT_EQUAL(1, fromData.alarmFlags);
  TEST_ASSERT_EQUAL(99, fromData.battery);
  TEST_ASSERT_EQUAL(0, fromData.manufacturer.compare("0001"));
  TEST_ASSERT_EQUAL_FLOAT(0.050150f, fromData.pressureBar);
  TEST_ASSERT_EQUAL_FLOAT(5.015000f, fromData.pressureKPa);
  TEST_ASSERT_EQUAL_FLOAT(0.727364f, fromData.pressurePsi);
  TEST_ASSERT_EQUAL_FLOAT(26.870001f, fromData.temperatureC);
  TEST_ASSERT_EQUAL_FLOAT(80.365997f, fromData.temperatureF);
}

void setup()
{
  // NOTE!!! Wait for >2 secs
  // if board doesn't support software reset via Serial.DTR/RTS
  delay(2000);
  UNITY_BEGIN(); // IMPORTANT LINE!
}

void loop()
{
  RUN_TEST(test_invalid_data);
  RUN_TEST(test_normal_data);
  UNITY_END(); // stop unit testing
}
