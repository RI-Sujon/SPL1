#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib")

void getHtmlPage(char *host)
{
	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;
	//char *host = "www.lged.gov.bd";
	struct hostent *serversock;
	char message[50000] , server_reply[200000];
	int recv_size;

	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		return 1;
	}
	//printf("Initialised.\n");

	if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d" , WSAGetLastError());
	}

	//printf("Socket created.\n");
    serversock = gethostbyname(host);
    if (serversock == NULL) printf("ERROR, no such host");

    memset(&server,0,sizeof(server));

	server.sin_family = AF_INET;
	server.sin_port = htons( 80 );
    memcpy(&server.sin_addr.s_addr,serversock->h_addr,serversock->h_length);

	if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		printf("connect error");
		return 1;
	}

	const char* msg = "GET /%s HTTP/1.0\r\nHost: %s\r\nUser-Agent: fetch.c\r\n\r\n";
	int status=sprintf(message,msg,"",host);
	//printf("status %s",message);
	if( status>=0&& send(s , message , strlen(message) , 0) < 0)
	{
		printf("Send failed");
		return 1;
	}
	//printf("Data Send\n");

	if((recv_size = recv(s , server_reply , 90000 , 0)) == SOCKET_ERROR)
	{
		printf("recv failed");
	}
	//printf("Reply received\n");

	server_reply[recv_size] = '\0';
    //printf(server_reply);

	 FILE *fptr ;
    fptr = fopen("program1.html","w") ;

    //printf("sss: %d\n" ,recv_size) ;

    int j ,flag = 0;
    for(j=0 ; j<recv_size ; j++)
    {
        if(server_reply[j]!='<' && flag==0)
        {
            continue ;
        }
        else flag = 1 ;

        if(flag == 1)fprintf(fptr,"%c",server_reply[j]) ;
    }
    fclose(fptr) ;
}
