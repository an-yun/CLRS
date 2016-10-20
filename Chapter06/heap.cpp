#include "list_heap.h"
#include "d_heap.h"
#include<winsock.h>  
#include<windows.h>  
#include<mysql.h>  
#include<stdio.h>  
#include<string.h>  
#include<stdlib.h> 
#pragma comment (lib, "libmysql.lib") 
#pragma comment (lib, "mysqlclient.lib") 
int main6_5_9()
{
	list_heap<int, 3> h{ list<int>{1,5,7,11},list<int>{2,4,6,8,9} ,list<int>{3,4,5,13,15} };
	h.bulid_min_heap();
	list<int> result;
	while (!h.empty())
	{
		result.push_back(h.increase_top());
		h.min_heapify();
	}
	for (auto num : result)cout << num << " ";
	return 0;
}
int main6_5_10()
{
	d_heap<int, 3, 10> h{9,8,7,6,54,37,15,46,9,4};
	h.d_heapsort();
	cout << h<<endl;
	h.d_heapsort_reverse();
	cout << h<<endl;
	h.d_heapsort();
	cout << h << endl;
	return 0;
}
int mainsql()
{
	MYSQL *connection;
	connection = mysql_init((MYSQL *)0);

	//Connect to the DB  
	if (mysql_real_connect(connection, "127.0.0.1", "root", "root", "test", 3306, NULL, 0))
	{
		printf("Succeed in connecting to the database !\n");
		//connection->
		MYSQL_RES   *mysql_ret;
		MYSQL_ROW   mysql_row;
		unsigned   long   num_rows;
		int ret  =  mysql_query(connection,"SELECT * FROM user");
		cout << ret << endl;
		if (!ret)
		{
			mysql_ret = mysql_store_result(connection);
			num_rows = mysql_num_rows(mysql_ret);
			while (mysql_row = mysql_fetch_row(mysql_ret))
			{
				cout << mysql_row[0]<<" "<< mysql_row[1] << " " << mysql_row[2]<<endl;
			}
		}
		mysql_close(connection);
	}
	return TRUE;
}