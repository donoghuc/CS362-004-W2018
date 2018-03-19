//UrlValidatorTest for UrlValidatorIncorrect

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }
   
   /*this is for partition test usage*/
   String[] validAuthority = new String[]{"www.google.com","go.au","255.255.255.255","255.com"};
   String[] invalidAuthority = new String[]{"","1.2.3.4.5","go.a",".aaa"};
   String[] validScheme = new String[]{"http://","h3t://","ftp://"};
   String[] invalidScheme = new String[]{"://","http:",""};
   String[] validPort= new String[]{":80",":65535",""};
   String[] invalidPort = new String[]{":-1",":65636",":65a"};
   String[] validPath= new String[]{"/test1","/$23","/test1/file"};
   String[] invalidPath=new String[]{"/../","/..","/test1//file1"};
   String[] validQuery=new String[]{"","?action=view","?q=dmv"};

   private int printExpected(String url, boolean result_expected, boolean result_observed) {
      //allow all test cases to run without hitting the assertion errors that stop test exectuion
      // print out the URL and the PASS FAIL
//    System.out.println(result_observed);
      if (result_expected == result_observed) {
         System.out.println(url + ", result expected = " + result_expected + ": PASSED TEST");
         return 0;
      }
      else {
         System.out.println(url + ", result expected = " + result_expected + ": FAILED TEST");
         return 1;
      }
   }
   
   public void testManualTest_0()
   {
      System.out.println("Manual test 0");

      UrlValidator urlVal = new UrlValidator(null,null, UrlValidator.ALLOW_ALL_SCHEMES);
      //A valid URL is made of <scheme>://<authority><port><path>?<query>
      int test_fails = 0;
      /*test valid scheme, empty authority, valid path, expect to be false */
      /*REPORT a bug finding here: http scheme allows empty authority */

      test_fails += printExpected("http:///path",false,urlVal.isValid("http:///path"));
      test_fails += printExpected("http://www.a-.gov",false,urlVal.isValid("http://www.a-.gov"));

      /*test valid scheme,authority,port, expect to be true */
      test_fails += printExpected("http://www.oregon.gov",true,urlVal.isValid("http://www.oregon.gov"));
      /*test valid scheme,authority,path,port, expect to be true */
      test_fails += printExpected("http://www.oregon.gov/ODOT",true,urlVal.isValid("http://www.oregon.gov/ODOT"));
      
      /*test valid scheme,authority,query,port, expect to be true */
      /*REPORT a bug finding here: as long as the path has two slashes, there will be errors */
      test_fails += printExpected("http://www.oregon.gov/Pages/search-results.aspx?q=dmv",true,urlVal.isValid("http://www.oregon.gov/Pages/search-results.aspx?q=dmv"));
      
      /*test valid scheme,authority,query,port, expect to be true */
      test_fails += printExpected("http://www.oregon.gov/search-results.aspx?q=dmv",true,urlVal.isValid("http://www.oregon.gov/search-results.aspx?q=dmv"));
      
      /*test incomplete but valid scheme, valid authority, port, expect to be true*/
      test_fails += printExpected("www.oregon.gov",false,urlVal.isValid("www.oregon.gov"));
      /*test invalid authority, valid scheme, port, expect to be false*/
      //REPORT a bug finding here: invalid authority will fail 
      test_fails += printExpected("http://www.a-.gov",false,urlVal.isValid("http://www.a-.gov"));
      
      /*test invalid scheme, valid authority, port, expect to be false*/
      /*REPORT a bug finding here: file:// https:// ftp:// scheme is not allowed, it will crush the program */
      //System.out.println(urlVal.isValid("file://www.oregon.gov"));
      test_fails += printExpected(":://www.oregon.gov",false,urlVal.isValid(":://www.oregon.gov"));
      //REPORT a bug finding here: empty scheme with incomplete authority will fail
      test_fails += printExpected("oregon.gov",false,urlVal.isValid("oregon.gov"));
      test_fails += printExpected("http://home",false,urlVal.isValid("http://home"));
      //System.out.println(urlVal.isValid("https://www.oregon.gov"));
      System.out.println("Test Fails: " + test_fails);
      System.out.println("Manual test 0 completed..\n");
      assertTrue(test_fails == 0);
      
      
   }
   
   public void testManualTest_1()
   {
      // This test shows the regex bug, basically anythin that is a "nested" link is falsely identified as invalid
      System.out.println("manual test 1");
      UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
      int test_fails = 0;
      test_fails += printExpected("http://www.google.com",true,urlVal.isValid("http://www.google.com"));
      test_fails += printExpected("http://www.google.com/thing/",true,urlVal.isValid("http://www.google.com/thing/"));
      test_fails += printExpected("http://www.google.com/thing/another",true,urlVal.isValid("http://www.google.com/thing/another"));
      System.out.println("Test Fails: " + test_fails);
      assertTrue(test_fails == 0);     
   }
   
   public void testManualTest_2()
   {   //This test shows the toLower _ toUpper bug
      // should be able to define custom schemes. in this case we allow only "http" and "bad" 
      // this implies that "https" should not be allowed
      System.out.println("manual test 2");
      String[] schemes = {"http","bad"};
      UrlValidator urlVal = new UrlValidator(schemes, 0);
      int test_fails = 0;
      test_fails += printExpected("http://www.google.com",true,urlVal.isValid("http://www.google.com"));
      test_fails += printExpected("bad://www.google.com",true,urlVal.isValid("bad://www.google.com"));
      test_fails += printExpected("https://www.google.com",false,urlVal.isValid("https://www.google.com"));
      System.out.println("Test Fails: " + test_fails);
      assertTrue(test_fails == 0);
   }
   
  public void testmanualTest_3()
  {   
     System.out.println("manual test 3");
     UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
     int test_fails = 0;
     test_fails += printExpected("file:///C:/Users/John/Desktop/donoghue_transcript_OSU.html",true,urlVal.isValid("file:///C:/Users/John/Desktop/donoghue_transcript_OSU.html"));
     System.out.println("Test Fails: " + test_fails);
     assertTrue(test_fails == 0);
  }
   
   
  public void testYourFirstPartition()
  {
     System.out.println("First Partition test starting here...\n");
     UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
     String url;
     int test_fails = 0;
     //test a valid authority + path/port/query
     for(int itr=0;itr<validAuthority.length;itr++){
        for(int base=0;base<validPath.length;base++){
           url="http://"+validAuthority[itr]+validPath[base];
           test_fails += printExpected(url,true,urlVal.isValid(url)); 
        } 
     }
     System.out.println();
     for(int itr=0;itr<validAuthority.length;itr++){
        for(int base=0;base<validPort.length;base++){
           url="http://"+validAuthority[itr]+validPort[base];
           test_fails += printExpected(url,true,urlVal.isValid(url)); 
        } 
     }
     System.out.println();
     for(int itr=0;itr<validAuthority.length;itr++){
        for(int base=0;base<validQuery.length;base++){
           url="http://"+validAuthority[itr]+validQuery[base];
           test_fails += printExpected(url,true,urlVal.isValid(url)); 
        } 
     }
     System.out.println();
     //test a invalid authority + path/port/query
     for(int itr=0;itr<invalidAuthority.length;itr++){
        for(int base=0;base<validPath.length;base++){
           url="http://"+invalidAuthority[itr]+validPath[base];
           test_fails += printExpected(url,false,urlVal.isValid(url)); 
        } 
     }
     System.out.println();
     for(int itr=0;itr<invalidAuthority.length;itr++){
        for(int base=0;base<validPort.length;base++){
           url="http://"+invalidAuthority[itr]+validPort[base];
           test_fails += printExpected(url,false,urlVal.isValid(url)); 
        } 
     }
     System.out.println();
     for(int itr=0;itr<invalidAuthority.length;itr++){
        for(int base=0;base<validQuery.length;base++){
           url="http://"+invalidAuthority[itr]+validQuery[base];
           test_fails += printExpected(url,false,urlVal.isValid(url)); 
        } 
     }
     assertTrue(test_fails == 0); 
  }
  
  public void testYourSecondPartition(){
     System.out.println("Second Partition test starting here...\n");
     long options = UrlValidator.ALLOW_ALL_SCHEMES;
     UrlValidator urlVal = new UrlValidator(null, null, options);
     String url;
//     Boolean result;
     int test_fails = 0;
     //test an invalid scheme + authority + Null/path/port/query
     for(int itr=0;itr<invalidScheme.length;itr++){
        for(int base=0;base<validAuthority.length;base++){
           url=(invalidScheme[itr]+validAuthority[base]).toString();
           test_fails += printExpected(url,false,urlVal.isValid(url)); 
        }
        
     }
     System.out.println();
     for(int itr=0;itr<invalidScheme.length;itr++){
        for(int base=0;base<validPort.length;base++){
           url=(invalidScheme[itr]+"www.abc.com"+validPort[base]).toString();
           test_fails += printExpected(url,false,urlVal.isValid(url)); 
        }
        
     }
     System.out.println();
     
     for(int itr=0;itr<invalidScheme.length;itr++){
        for(int base=0;base<validPath.length;base++){
           url=(invalidScheme[itr]+"www.abc.com"+validPath[base]).toString();
           test_fails += printExpected(url,false,urlVal.isValid(url)); 
        }
     }
     System.out.println();
     
     //test a valid scheme + authority + NULL/path/port/query
     /*BUG report: any schema other than http will run into crush as a result of RegexValidator authorityValidator failure*/
     for(int itr=0;itr<validScheme.length;itr++){
        for(int base=0;base<validAuthority.length;base++){
           url=(validScheme[itr]+validAuthority[base]).toString();
           test_fails += printExpected(url,true,urlVal.isValid(url)); 
        }
        //System.out.printf("Due to RegexValidator authorityValidator failure, scheme other than http will crush the program.\n ");
     }
     System.out.println();
     
     for(int itr=0;itr<validScheme.length;itr++){
        for(int base=0;base<validPort.length;base++){
           url=(validScheme[itr]+"www.abc.com"+validPort[base]).toString();
           test_fails += printExpected(url,true,urlVal.isValid(url)); 
        }
        //System.out.printf("Due to RegexValidator authorityValidator called by isValidAuthority() function, scheme other than http will crush the program.\n ");
     }
     System.out.println();
     
     for(int itr=0;itr<validScheme.length;itr++){
        for(int base=0;base<validPath.length;base++){
           url=(validScheme[itr]+"www.abc.com"+validPath[base]).toString();
           test_fails += printExpected(url,true,urlVal.isValid(url)); 
        }
        //System.out.printf("Due to RegexValidator authorityValidator called by isValidAuthority() function, scheme other than http will crush the program.\n ");
     }
     System.out.println();
     assertTrue(test_fails == 0); 
     System.out.println("Second Partition test complted...\n");

  }
   
  public void testIsValid()
  {
      //You can use this function for programming based testing
      String schemes[] = {"http", "https", "ftp"};
      String validScheme = "http://";
      String validAuthority = "www.google.com";
      String validPath = "/search";
      String validPort = ":80";
      String validQuery = "?q=hello+world";
      int testFails = 0;
      
      //Restrict schemes to above schemes array 
      UrlValidator urlVal = new UrlValidator(schemes, 0);
      //assertTrue(urlVal.isValid(validScheme + validAuthority + validPort + validPath + validQuery));
      
      System.out.println("\nPROGRAMMING-BASED TESTS FOR UrlValidator");
      System.out.println("\nNOW TESTING WITH KNOWN FULLY VALID URL:");
      if(printExpected(validScheme + validAuthority + validPort + validPath + validQuery, true, urlVal.isValid(validScheme + validAuthority + validPort + validPath + validQuery)) > 0)
      {
         System.out.println("\nDEFINITE ISSUE WITH UrlValidator. PLEASE DEBUG.");
         if(!urlVal.isValidScheme(validScheme))
         {
            System.out.println("*There is an issue with scheme validity test.");
         }
         // Giving ClassNotDefined error for DomainValidator class - Aaron
         if(!urlVal.isValidAuthority(validAuthority))
         {
            System.out.println("*There is an issue with authority validity test.");
         }
         if(!urlVal.isValidPath(validPath))
         {
            System.out.println("*There is an issue with path validity test.");
         }
         if(!urlVal.isValidQuery(validQuery))
         {
            System.out.println("*There is an issue with query validity test.");
         }
      }
      
      System.out.println("\nNOW TESTING URL SCHEME VALIDITY TEST:");
      
      for(int i = 0; i < testSchemeCase.length; i++)
      {
         testFails += printExpected(testSchemeCase[i].item + validAuthority + validPort + validPath + validQuery, testSchemeCase[i].valid, urlVal.isValid(testSchemeCase[i].item + validAuthority + validPort + validPath + validQuery));
      }
      if(testFails > 0)
      {
         System.out.println("Issue with URL validity tests.");
      }

      testFails = 0;
      
      // Allow all schemes so we know test is not failing on scheme
      urlVal = new UrlValidator(null,null, UrlValidator.ALLOW_ALL_SCHEMES);
      System.out.println("\nNOW TESTING URL AUTHORITY VALIDITY TEST:");
      for(int i = 0; i < testAuthority.length; i++)
      {
         testFails += printExpected(validScheme + testAuthority[i].item + validPort + validPath + validQuery, testAuthority[i].valid, urlVal.isValid(validScheme + testAuthority[i].item + validPort + validPath + validQuery));
      }
      if(testFails > 0)
      {
         System.out.println("Issue with URL validity tests.");
      }

      testFails = 0;
      System.out.println("\nNOW TESTING URL PATH VALIDITY TEST:");
      for(int i = 0; i < testPath.length; i++)
      {
         testFails += printExpected(validScheme + validAuthority + validPort + testPath[i].item + validQuery, testPath[i].valid, urlVal.isValid(validScheme + validAuthority + validPort + testPath[i].item + validQuery));
      }
      if(testFails > 0)
      {
         System.out.println("Issue with URL validity tests.");
      }

      testFails = 0;
      System.out.println("\nNOW TESTING URL QUERY VALIDITY TEST:");
      for(int i = 0; i < testQuery.length; i++)
      {
         testFails += printExpected(validScheme + validAuthority + validPort + validPath + testQuery[i].item, testQuery[i].valid, urlVal.isValid(validScheme + validAuthority + validPort + validPath + testQuery[i].item));
      }
      if(testFails > 0)
      {
         System.out.println("Issue with URL validity tests.");
      }
      
      // Restrict schemes again
      urlVal = new UrlValidator(schemes, 0);
      testFails = 0;
      System.out.println("\nNOW TESTING RANDOMLY CONSTRUCTED URLS (ONLY TEST FAILURES WILL BE DISPLAYED):");
      for(int i = 0; i < 10000; i++)
      {
         int testSchemeIndex = (int)(Math.random()*(testSchemeCase.length));
         int testAuthorityIndex = (int)(Math.random()*(testAuthority.length));
         int testPortIndex = (int)(Math.random()*(testPort.length));
         int testPathIndex = (int)(Math.random()*(testPath.length));
         int testQueryIndex = (int)(Math.random()*(testQuery.length));
         
         if((testSchemeCase[testSchemeIndex].valid && testAuthority[testAuthorityIndex].valid && testPort[testPortIndex].valid && testPath[testPathIndex].valid && testQuery[testQueryIndex].valid) != urlVal.isValid(testSchemeCase[testSchemeIndex].item + testAuthority[testAuthorityIndex].item + testPort[testPortIndex].item + testPath[testPathIndex].item + testQuery[testQueryIndex].item))
         {     
            testFails += printExpected(testSchemeCase[testSchemeIndex].item + testAuthority[testAuthorityIndex].item + testPort[testPortIndex].item + testPath[testPathIndex].item + testQuery[testQueryIndex].item, 
               (testSchemeCase[testSchemeIndex].valid && testAuthority[testAuthorityIndex].valid && testPort[testPortIndex].valid && testPath[testPathIndex].valid && testQuery[testQueryIndex].valid), 
               urlVal.isValid(testSchemeCase[testSchemeIndex].item + testAuthority[testAuthorityIndex].item + testPort[testPortIndex].item + testPath[testPathIndex].item + testQuery[testQueryIndex].item)); 
         }
      }
      System.out.println("\nThere were " + testFails + " random test failures.");
  }
      // ResultPair(item, valid)
      // Boolean 'valid' value is only correct for testSchemeCase when UrlValidator is constructed with allowed schemes equal to {"http", "https", "ftp"}
      ResultPair[] testSchemeCase = {new ResultPair("HTTP://", true),
                              new ResultPair("http://", true), 
                              new ResultPair("ftp://", true),
                              new ResultPair("FTP://", true),
                              new ResultPair("HTTPS://", true),
                              new ResultPair("https://", true),
                              new ResultPair("", false),
                              new ResultPair("foo://", false),
                              new ResultPair("FOO://", false),
                              new ResultPair("://", false),
                              new ResultPair("/", false)};
      
      ResultPair[] testAuthority = {new ResultPair("www.youtube.com", true),
               new ResultPair("reddit.com", true), 
               new ResultPair("oregonstate.edu", true),
               new ResultPair("www.dol.wa.gov", true),
               new ResultPair("4.3.2.1", true),
               new ResultPair("250.251.252.253", true),
               new ResultPair("500", false),
               new ResultPair("jfuirhwf", false),
                  new ResultPair("-5.-5.-5.-5", false),
                  new ResultPair(".,l", false),
                  new ResultPair("", false),
                  new ResultPair("---", false)};
      
      ResultPair[] testPath = {new ResultPair("/search", true),
            new ResultPair("/yes/", true), 
            new ResultPair("/no/yes", true),
            new ResultPair("", true),
            new ResultPair("/", true),
            new ResultPair(".500", false),
            new ResultPair("/..", false),
               new ResultPair("/../", false),
               new ResultPair("/yes//no", false)};
      
      ResultPair[] testPort = {new ResultPair(":80", true),
              new ResultPair(":65535", true),
              new ResultPair(":0", true),
              new ResultPair("", true),
              new ResultPair(":-1", false),
             new ResultPair(":65636",false),
              new ResultPair(":65a", false)};

      ResultPair[] testQuery = {new ResultPair("?action=view", true),
              new ResultPair("?action=edit&mode=up", true),
              new ResultPair("", true)};
}