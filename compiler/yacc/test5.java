/*Test file: Duplicate declaration in different scope and same scope*/
class Point
{
	boolean test()
	{
		for(int i=0, j=0; j<i && true; --j)
		{
			if(j == 0) break;
			else
			{
				continue;
			}
		}

		try
		{

		}catch(Exception e)
		{
			print(e);
		}
		finally
		{

		}
	}
}
class Test
{
	Point p = new Point();
	switch(a)
	{
		case 1: print(a);
		case 2: print(a+1);break;
		default: print(a++);
	}
}
class Test2 extends Test
{
	Point p = new Point();

	this.a = b;

	do
	{

	}while(false);
}
class Test3 implements Point, Test2
{
	Point p = new Point();
	p.test(a, b, c);
}
