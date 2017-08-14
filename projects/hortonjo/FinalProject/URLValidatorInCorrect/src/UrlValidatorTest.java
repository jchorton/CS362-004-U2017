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
   public void testManualTest() {
	   checkURL("http://www.google.com", true);	   	   
  	   checkURL("https://oregonstate.instructure.com/courses/1638968", true);
	   //checkURL("https://www.wunderground.com/cgi-bin/findweather/getForecast?query=corvallis+oregon", true); //BUG: Doesn't accept all queries
	   checkURL("http://www.oregon.gov/SiteCollectionImages/branding/portal/bigfoot.png", true);
	   //checkURL("http://111.222.333.444", false);	// BUG: Doesn't recognize out-of-range   
	   checkURL("http://192.168.1.1", true);
	   //checkURL("//example.com", true); // BUG: Requires scheme, protocol relative URLs do not work (CORRECT VERSION ALSO DOES NOT WORK)
	   checkURL("http://192.168.1.1", true);
	   checkURL("ftp://ftp.nifc.gov/", true);
	   //checkURL("mailto:test.student@oregonstate.edu", true);  // BUG: Doesn't accept email links
	   checkURL("123invalid-scheme://192.168.0.1/", false);
	   checkURL("a123://192.168.0.1/", true);
   	   checkURL("http://www.google.com:80/", true);
   	   checkURL("http://www.google.com/#pickles", true);
   	   checkURL("http://www.google.com/$%^&*()", false);
   	   checkURL("http://www.domain.silly", false);
   	   checkURL("https://///www.google.com", false);
   	   checkURL("https://www..google.com", false);
   	   checkURL("https://www.google.com/hello//there", false);
   }

   
   /*******************
    * Partition tests *
    *******************/
   // URLs with specified ports
   public void testPartition1() {
	   checkURL("http://www.amazon.com:80", true);
	   checkURL("ftp://ftp.soylent.com:123", true);
	   checkURL("http://secretlab.gov:1000", true); // BUG: 4-digit port numbers fail
   }
   
   // URLs with specified paths
   public void testPartition2() {
	   checkURL("http://www.amazon.com/a", true);
	   checkURL("http://www.amazon.com/a/b", true);
	   checkURL("http://www.amazon.com/a/b/c", true);
	   checkURL("http://www.amazon.com/a/b/c/d", true);
	   checkURL("http://www.amazon.com/a/b/c/d/penguin.gif", true);
   }
   
   // URLs with #references
   public void testPartition3() {
	   checkURL("http://www.amazon.com/#1", true);
	   checkURL("ftp://ftp.google.com/#secretRoom", true);
   }
   
   // URLs with queries
   public void testPartition4() { // BUG: Queries don't work at all
	   checkURL("http://www.example.com/showNumber?query=123", true);
	   checkURL("http://www.example.com/showNumber?key1=value1&key2=value2", true);
	   checkURL("https://www.wunderground.com/cgi-bin/findweather/getForecast?query=corvallis+oregon", true);
   }
   
   
   /*****************************
    * Programming-based Testing *
    *****************************/
   // Runs through valid IP addresses with a bit of overrun
   public void testValidIPTest() {
	   String urlString = "";
	   for (int i = 0; i < 300; i++) {
		   urlString = "http://";
		   urlString += i + "." + i + "." + i + "." + i; // http://i.i.i.i
		   if (i < 256)
			   checkURL(urlString, true);
		   else
			   checkURL(urlString, false);
	   }
   }
   
   // Runs through all valid port numbers
   public void testValidPortTest() {
	   String urlString = "";
	   for (int i = 0; i < 70000; i++) {
		   urlString = "http://www.example.com:";
		   urlString += i; // http://www.example.com:i
		   if (i < 65535)
			   checkURL(urlString, true);
		   else
			   checkURL(urlString, false);
	   }
   }
   
   // Checking an extremely simple query
   public void testUnitTest1() {
	   checkURL("http://www.example.com/showNumber?query=123", true);
   }

   
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */

}
