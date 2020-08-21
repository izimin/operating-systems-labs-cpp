#pragma onec

class MyClass
{
public:
	MyClass(int num);	
	int divs();
	int rev();

private:
	int x;
};

MyClass :: MyClass(int num)
{
	x = num;
}

int MyClass :: rev()
{
	int  d = 0, i = x;
	bool neg = (i < 0);
	
	if(neg) i = 0 - i;

	while(i != 0)
	{
		d  = d*10 + (i % 10);
		i /= 10;
	}

	if(neg) d = 0 - d;

	return d;
}

int MyClass :: divs()
{
	if ((x >= 0) && (x <= 2))
		return x;
	
	int k = 0;

	while((x & 1) == 0)
	{
		++k;
		x >>= 1;
	}

	if (x == 1) return k+1;

	int cnt = k + 1;

	for (int i = 3; (i*i) <= x; i += 2)
	{
		k = 0;
		while ((x % i) == 0)
		{
			++k;
			x /= i;
		}
		cnt *= (k + 1);
	}

	if(x > 1) cnt <<= 1;

	return cnt;
}

extern "C" __declspec(dllexport) int CountDivsNumber(int x)
{
	MyClass MC(x);
	return MC.divs();
}

extern "C" __declspec(dllexport) int Rev(int x)
{
	MyClass MC(x);
	return MC.rev();
}