Lex, Yacc 版本

$ flex --version
flex 2.6.0

$ bison --version
bison (GNU Bison) 3.0.4

作業平台

$ uname --all
Linux jimmy-sdcz880 4.8.0-52-generic #55~16.04.1-Ubuntu SMP Fri Apr 28 14:36:29 UTC 2017 x86_64 x86_64 x86_64 GNU/Linux

執行方式

$ make
$ ./a.out < test1.java 

Line: 2: class sigma {
Line: 3:   final int n = 10;
Line: 4:   int sum, index;
Line: 5:   
Line: 6:   main()
Line: 7:   {
Line: 8:     index = 0;
Line: 9:     sum = 0;
Line: 10:     while (index <= n) 
Line: 11:     {
Line: 12:       sum = sum + index;
Line: 13:       index = index + 1;
Line: 14:     } 
Line: 15:     print(sum);
Line: 16:   }   
Line: 17: } 

$ ./a.out < test2.java 

Line: 2: class Point
Line: 3: {
Line: 4: 	static int counter ;
Line: 5: 	int x, y ;
Line: 6: 	
Line: 7: 	int x ;
> ERROR : Line 6 at 5 'x' is a duplicate identifier.

Line: 8: 	void clear()
Line: 9: 	{
Line: 10: 		x = 0 ;
Line: 11: 		y = 0 ;
Line: 12: 	}
Line: 13: }

$ ./a.out < test3.java 

Line: 2: class Point {
Line: 3: 	int z;
Line: 4: 	
Line: 5: 	int x y ;
> ERROR : Line 5 at 5 [y] has syntax error. 

Line: 6: 	float w;
Line: 7: }
Line: 8: class Test {
Line: 9: 	int d;
Line: 10: 	
Line: 11: 	Point p = new Point()
Line: 12: 	int w,q;
> ERROR : Line 12 at 1 [int] has syntax error. 

Line: 13: }

$ ./a.out < test4.java 

Line: 2: class Point
Line: 3: {
Line: 4: 	int x, y ;
Line: 5: 	int p;
Line: 6: 	boolean test()
Line: 7: 	{
Line: 8: 		
Line: 9: 		int x;
> ERROR : Line 8 at 5 'x' is a duplicate identifier.

Line: 10: 		float w;
Line: 11: 		
Line: 12: 		char x;
> ERROR : Line 11 at 6 'x' is a duplicate identifier.

Line: 13: 		{
Line: 14: 			
Line: 15: 			boolean x;
> ERROR : Line 14 at 9 'x' is a duplicate identifier.

Line: 16: 		}
Line: 17: 		
Line: 18: 		int w;
> ERROR : Line 17 at 5 'w' is a duplicate identifier.

Line: 19: 	}
Line: 20: }
Line: 21: class Test
Line: 22: {
Line: 23: 	
Line: 24: 	Point p = new Point();
Line: 25: }

如何處理這份規格書上的問題

按照 105-CompilerLab-SimpleJava-Parser.pdf 裡面提到的 syntactic definitions
熟悉後自己新增像是 try catch finally, switch case default, do while, class extends, class implements
因為 loop 中的 condition 可能有 continue, break 要拉出來特別寫

這個作業所遇到的問題

摸索的時候很費力，因為完全不了解 yacc 的執行方式，後面看懂後新增東西就比較順手

test5.java 我為了測試自己加的東西是否成功的測試檔

$ ./a.out < test5.java 

Line: 2: class Point
Line: 3: {
Line: 4: 	boolean test()
Line: 5: 	{
Line: 6: 		for(int i=0, j=0; j<i && true; --j)
Line: 7: 		{
Line: 8: 			if(j == 0) break;
Line: 9: 			else
Line: 10: 			{
Line: 11: 				continue;
Line: 12: 			}
Line: 13: 		}
Line: 14: 
Line: 15: 		try
Line: 16: 		{
Line: 17: 
Line: 18: 		}catch(Exception e)
Line: 19: 		{
Line: 20: 			print(e);
Line: 21: 		}
Line: 22: 		finally
Line: 23: 		{
Line: 24: 
Line: 25: 		}
Line: 26: 	}
Line: 27: }
Line: 28: class Test
Line: 29: {
Line: 30: 	Point p = new Point();
Line: 31: 	switch(a)
Line: 32: 	{
Line: 33: 		case 1: print(a);
Line: 34: 		case 2: print(a+1);break;
Line: 35: 		default: print(a++);
Line: 36: 	}
Line: 37: }
Line: 38: class Test2 extends Test
Line: 39: {
Line: 40: 	Point p = new Point();
Line: 41: 
Line: 42: 	this.a = b;
Line: 43: 
Line: 44: 	do
Line: 45: 	{
Line: 46: 
Line: 47: 	}while(false);
Line: 48: }
Line: 49: class Test3 implements Point, Test2
Line: 50: {
Line: 51: 	Point p = new Point();
Line: 52: 	p.test(a, b, c);
Line: 53: }


