/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;


/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {
   
   public UrlValidatorTest(String testName) {
	   super(testName);
   }
   
   // This will check the given URL to make sure it matches expectation
   public void checkURL(String url, boolean validity) {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   // Prints out the URL that returned the wrong value and registers failure
	   if (urlVal.isValid(url) != validity) {
		   System.out.println("Unexpected Validity: " + url);
		   fail("Unexpected Validity: " + url);
	   }
   }
   
   
   /****************
    * Manual Tests *
    ****************/
   public void testManualTest1() {
	   checkURL("http://www.google.com", true);	   	   
   }
   
   public void testManualTest2() { 
	   checkURL("https://oregonstate.instructure.com/courses/1638968", true);
   }
   
   public void testManualTest3() { // BUG: Doesn't accept all queries
	   checkURL("https://www.wunderground.com/cgi-bin/findweather/getForecast?query=corvallis+oregon", true);
   }
   
   public void testManualTest4() {
	   checkURL("http://www.oregon.gov/SiteCollectionImages/branding/portal/bigfoot.png", true);
   }
   
   public void testManualTest5() { // BUG: Doesn't recognize out-of-range
	   checkURL("http://111.222.333.444", false);
   }
   
   public void testManualTest6() {
	   checkURL("http://192.168.1.1", true);
   }
  
   public void testManualTest7() { // BUG: Requires scheme, protocol relative URLs do not work
	   checkURL("//example.com", true);
   }

   public void testManualTest8() {
	   checkURL("http://192.168.1.1", true);
   }
   
   public void testManualTest9() {
	   checkURL("ftp://ftp.nifc.gov/", true);
   }   
   
   public void testManualTest10() { // BUG: Doesn't accept email links, could be the @ symbol?
	   checkURL("mailto:test.student@oregonstate.edu", true);
   } 
   
   public void testManualTest11() {
	   checkURL("123invalid-scheme://192.168.0.1/", false);
   } 
   
   public void testManualTest12() {
	   checkURL("http://www.google.com:80/", true);
   }

   public void testManualTest13() {
	   checkURL("http://www.google.com/#pickles", true);
   }
   
   public void testManualTest14() {
	   checkURL("http://www.google.com/$%^&*()", false);
   }
   
   public void testManualTest15() {
	   checkURL("http://www.domain.silly", false);
   }
   
   public void testManualTest16() {
	   checkURL("https://///www.google.com", false);
   }

   
   /*******************
    * Partition tests *
    *******************/
   // URLs with specified ports
   public void testYour1Partition() {
	   checkURL("http://www.amazon.com:80", true);
	   checkURL("ftp://ftp.soylent.com:123", true);
	   checkURL("http://secretlab.gov:1000", true); // BUG: 4-digit port numbers fail
   }
   
   // URLs with specified paths
   public void testYour2Partition() {
	   checkURL("http://www.amazon.com/a", true);
	   checkURL("http://www.amazon.com/a/b", true);
	   checkURL("http://www.amazon.com/a/b/c", true);
	   checkURL("http://www.amazon.com/a/b/c/d", true);
	   checkURL("http://www.amazon.com/a/b/c/d/penguin.gif", true);
   }
   
   // URLs with #references
   public void testYour3Partition() {
	   checkURL("http://www.amazon.com/#1", true);
	   checkURL("ftp://ftp.google.com/#secretRoom", true);
   }
   
   // URLs with queries
   public void testYour4Partition() { // BUG: Queries don't work at all
	   checkURL("http://www.example.com/showNumber?query=123", true);
	   checkURL("http://www.example.com/showNumber?key1=value1&key2=value2", true);
	   checkURL("https://www.wunderground.com/cgi-bin/findweather/getForecast?query=corvallis+oregon", true);
   }
   
   
   /*****************************
    * Programming-based Testing *
    *****************************/
   public void testIsValid()
   {
	   for(int i = 0;i<10000;i++)
	   {
		   
	   }
   }
   
   public void testAnyOtherUnitTest()
   {
	   
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   

}
