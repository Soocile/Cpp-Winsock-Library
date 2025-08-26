
#ifndef NONCOPYABLE_HPP
#define NONCOPYABLE_HPP

namespace Net {

	class NonCopyable {

	protected:

		//default constructor and destructor
		NonCopyable() = default;
		~NonCopyable() = default;



	private:

		NonCopyable(const NonCopyable&) = delete;
		NonCopyable& operator=(const NonCopyable&) = delete;
		
	};


}



#endif // NONCOPYABLE_HPP