#ifndef _DEFINE_H
#define _DEFINE_H

#define DECLARE_SINGLETON(class_name); \
	public: \
	static class_name* instance(void); \
	private: \
	static class_name* instance_; \
	public: \

#define DEFINE_SINGLETON(class_name) \
	class_name* class_name::instance_ = 0; \
	class_name* class_name::instance(void) \
	{ \
		if(instance_ == 0) { \
		instance_ = new class_name(); \
		} \
		return instance_; \
	} \


#endif
