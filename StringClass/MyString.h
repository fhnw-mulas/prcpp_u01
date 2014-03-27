#include <iostream>
#include <memory>

using namespace std;

class String final { 
	
	private:

		size_t m_len;						 
		shared_ptr<char> m_string;
		size_t m_start;

	public:								

		shared_ptr<char> getstring(){
			return m_string;
		}

		// Class constructors
		String();						
		String(const String& s);
		String(const char* c);
		String(String&& s);

		// Class methods
		char charAt(size_t index) const;
		int compareTo(const String& s) const;
		String concat(char c) const;
		String concat(const String& s) const; 
		size_t length() const;
		String substring(size_t beg, size_t end) const;
		int toInt() const;
		unique_ptr<char[]> toCString() const;
		bool operator==(const String& s) const { return compareTo(s) == 0; }

		// Static class methods
		static String valueOf(int number);

		friend ostream& operator<<(ostream& os, const String& s) { 
			const size_t end = s.m_start + s.m_len; 
			const char* const sc = s.m_string.get();
			for(size_t i=s.m_start; i < end; i++) 
				os << sc[i]; return os; 
		}

		String & String::operator=(String&& s){
			if (this != &s){

				m_len = s.m_len;
				m_start = s.m_start;
				m_string = s.m_string;

				s.m_len = 0;
				s.m_start = 0;
				s.m_string = nullptr;
			}
			return *this;
		}

};