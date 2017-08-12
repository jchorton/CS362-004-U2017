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
import java.util.Random;


/**
 * Performs Random Validation Test for url validations.
 * CS362 Extra Credit
 * Jonathan Horton -- hortonjo@oregonstate.edu
 * 
 * What this test does NOT check:
 * - alternate domains
 * - mailto: (which isValid doesn't seem to recognize anyway)
 * - length of components
 * - protocol relative URLs such as "//example.com" (isValid doesn't seem to recognize them either)
 * - things like "." and "/" aren't entirely random since they have extra rules
 * - false statements
 */
public class UrlValidatorRandomTest extends TestCase {

	public UrlValidatorRandomTest(String testName) {
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

	// Generates a random boolean value - true or false
	public static boolean randBool() {
		Random rand = new Random();
		return rand.nextBoolean();
	}
	
	// Generates a random integer in the given range
	public static int randInt(int min, int max) {
		Random rand = new Random();
		return rand.nextInt((max - min) + 1) + min;
	}
	
	// Generates a string of the given number of letters
	// (https://stackoverflow.com/questions/41107/how-to-generate-a-random-alpha-numeric-string)
	public static String randChars(int num) {
		String validChars = 
				"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz$-_+!*'(),";
		int validLen = validChars.length();
		
		String randChars = "";
		for (int i = 0; i < num; i++) {
			randChars += validChars.charAt(randInt(0, validLen - 1));
		}
		
		return randChars;
	}
	
	// Same as above, but restricted to just lower-case letters
	public static String randAlpha(int num) {
		String validChars = 
				"abcdefghijklmnopqrstuvwxyz";
		int validLen = validChars.length();
		
		String randAlpha = "";
		for (int i = 0; i < num; i++) {
			randAlpha += validChars.charAt(randInt(0, validLen - 1));
		}
		
		return randAlpha;
	}
	
	// Same as above, but restricted to just lower-case letters and numbers
	public static String randAlphaNum(int num) {
		String validChars = 
				"0123456789abcdefghijklmnopqrstuvwxyz";
		int validLen = validChars.length();
		
		String randAlphaNum = "";
		for (int i = 0; i < num; i++) {
			randAlphaNum += validChars.charAt(randInt(0, validLen - 1));
		}
		
		return randAlphaNum;
	}
	
	// Generates and returns a protocol that follows requirements
	public static String protocolString() {
		String protocolString = "";
		protocolString += randAlpha(1);
		
		int num = randInt(0, 5);
		protocolString += randAlphaNum(num);
		
		protocolString += "://";
		
		return protocolString;
	}
	
	// Generates a hostname of reasonable length
	public static String hostString() {
		String hostString = "";
		int numBreaks = randInt(1, 5); // may tweak maximum
		int numLetters;
		
		for (int i = 0; i < numBreaks; i++) {
			numLetters = randInt(1, 8); // may tweak maximum
			hostString += randAlpha(numLetters);
			hostString += ".";
		}
		
		hostString += "com"; // fixed domain!
		return hostString;
	}
	
	// Generates a random IP address if that's what we want
	public static String ipString() {
		String ipString = "";
		for (int i = 0; i < 3; i++) {
			ipString += randInt(0, 255);
			ipString += ".";
		}
		ipString += randInt(0, 255);
		
		return ipString;
	}
	
	
	// Generates a string that uses a random port number
	public static String portString() {
		int num = randInt(1, 65535);
		String portString = ":" + num;
		return portString;
	}

	// Generates a random path of reasonable length
	public static String pathString() {
		String pathString = "";
		int numBreaks = randInt(1, 5); // may tweak maximum
		int numLetters;
		
		for (int i = 0; i < numBreaks; i++) {
			pathString += "/";
			numLetters = randInt(1, 8); // may tweak maximum
			pathString += randChars(numLetters);
		}
		
		return pathString;
	}
	
	// Generates a random query of reasonable length
	public static String queryString() {
		String queryString = "?";
		int numValues = randInt(1, 3); // may tweak maximum
		int numLetters;
		
		for (int i = 0; i < numValues; i++) {
			numLetters = randInt(1, 4); // may tweak maximum
			queryString += randChars(numLetters);
			queryString += "=";
			numLetters = randInt(1, 10); // may tweak maximum
			queryString += randChars(numLetters);
		}
		
		return queryString;
	}
	
	// Generates a random reference of reasonable length
	public static String refString() {
		String refString = "#";
		int numLetters = randInt(1, 10); // may tweak maximum
		refString += randChars(numLetters);
		return refString;
	}

	// Constructs the full URL by calling on different randomizing components
	public static String generateURL() {
		String urlString = "";
		boolean boolHost, boolPort, boolPath, boolQuery, boolRef; // if we want these parts
		
		urlString += protocolString();
		
		boolHost = randBool();
		if (boolHost) {	
			urlString += hostString();
		} else {
			urlString += ipString();
		}
		
		boolPort = randBool();
		if (boolPort) {
			urlString += portString();
		}
		
		boolPath = randBool();
		if (boolPath) {
			urlString += pathString();
		}
		
		boolQuery = randBool();
		if (boolQuery) {
			urlString += queryString();
		}
		
		boolRef = randBool();
		if (boolRef) {
			urlString += refString();
		}
		
		return urlString;
	}
	
	// Checks thousands of randomly generated URLs for validity!
	public void testRandomURL() {
		String urlString;
		checkURL("123bad_url", false); // checks false
		checkURL("http://www.google.com", true); // checks true
		
		for (int i = 0; i < 100000; i++) {
			urlString = generateURL();
			checkURL(urlString, true);
			System.out.println("URL: " + urlString); // TODO: Uncomment to see all checked URLs!
		}
	}

}
