#include "stdafx.h" 
#include "CppUnitTest.h" 
#include "MyString.h" 
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
	TEST_CLASS(MyString) {

		public:
			TEST_METHOD(Construction) {
				String s0;
				String s1("");
				String s2("abc");
				String s00(s0);
				String s11(s1);
				String s22(s2);
				String s33(move(s1));
			}

			TEST_METHOD(Length) {
				Assert::IsTrue(String().length() == 0);
				Assert::IsTrue(String("").length() == 0);
				Assert::IsTrue(String("abc").length() == 3);
			}

			TEST_METHOD(toCString){
				Assert::AreEqual(String().toCString().get(), "");
				Assert::AreEqual(String("abc").toCString().get(), "abc");
			}

			TEST_METHOD(charAt) {
				String tmp = String("abc");
				Assert::IsTrue(tmp.charAt(0) == 'a');
				Assert::IsTrue(tmp.charAt(2) == 'c');

				try{
					tmp.charAt(3);
					Assert::Fail();
				}
				catch (exception e){ }
				
				try{
					tmp.charAt(4);
					Assert::Fail();
				}
				catch (exception e){ }

				try{
					tmp.charAt(-1);
					Assert::Fail();
				}
				catch (exception e){ }

			}

			TEST_METHOD(compareTo) {
				String s1 = String("aaa");
				String s2 = String("aaaa");
				String s3 = String("aab");
				String s4 = String("");
				String s5 = String("");
				String s6 = String("aaa");

				Assert::IsTrue(s1.compareTo(s2) == -1);
				Assert::IsTrue(s1.compareTo(s3) == -1);
				Assert::IsTrue(s2.compareTo(s3) == -1);
				Assert::IsTrue(s4.compareTo(s1) == -1);
				Assert::IsTrue(s4.compareTo(s2) == -1);

				Assert::IsTrue(s1.compareTo(s4) == 1);
				Assert::IsTrue(s3.compareTo(s2) == 1);
				Assert::IsTrue(s3.compareTo(s1) == 1);
				Assert::IsTrue(s2.compareTo(s1) == 1);

				Assert::IsTrue(s1.compareTo(s6) == 0);
				Assert::IsTrue(s4.compareTo(s5) == 0);
			}

			TEST_METHOD(concat){
				String s1 = String("Hell");
				String s2 = String("Hello");
				String s3 = String("Worl");
				String s4 = String("World");

				Assert::IsTrue(s1.concat('o') == "Hello");
				Assert::IsTrue(s2.concat(s4) == "HelloWorld");
				Assert::IsTrue(s1.concat('o').concat(s3.concat('d')) == "HelloWorld");
			}

			TEST_METHOD(substring){
				String s1 = String("abcd");

				Assert::IsTrue(s1.substring(1, 2) == "b");
				Assert::IsTrue(s1.substring(2, 1) == "");
				Assert::IsTrue(s1.substring(5, 100) == "");
			}

			TEST_METHOD(ValueOf){
				Assert::IsTrue(String::valueOf(15896) == "15896");
				Assert::IsTrue(String::valueOf(-58997) == "-58997");
				Assert::IsTrue(String::valueOf(0) == "0");
			}

	};
}