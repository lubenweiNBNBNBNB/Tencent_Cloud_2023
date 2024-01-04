#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <unordered_set>
#include <unordered_map>
using namespace std;

class HeapOnly
{
public:
	static HeapOnly* CreateObj(int x = 0)
	{
		HeapOnly* p = new HeapOnly(x);//堆上
		return p;
	}

private:
	HeapOnly(int x = 0)
		:_x(x)
	{}

	HeapOnly(const HeapOnly& hp) = delete;
	HeapOnly& operator=(const HeapOnly& hp) = delete;

	int _x;
};

class StackOnly
{
public:
	static StackOnly CreateObj(int x = 0)
	{
		return StackOnly(x);
	}

	StackOnly(StackOnly&& st)
		:_x(st._x)
	{}

private:
	StackOnly(int x = 0)
		:_x(x)
	{}

	StackOnly(const StackOnly& st) = delete;

	int _x;
};

int main()
{
	//HeapOnly a;无参构造不可访问
	//static HeapOnly c;
	HeapOnly* a = HeapOnly::CreateObj();
	HeapOnly* b = a;
	//HeapOnly d();函数
	//HeapOnly e(*a);拷贝构造不可访问
	//HeapOnly f = *a;

	//StackOnly g;无参构造不可访问
	//static StackOnly h;
	//StackOnly i = new StackOnly;

	//StackOnly j = StackOnly::CreateObj();
	//static StackOnly k = j;
	return 0;
}
