CC		= g++ -std=c++2a
THREADFLAG	= -lpthread
GET_EXE_NAME    	= -o
SERVER_MAIN_NAME  	= main-server.cpp 
CLIENT_MAIN_NAME  	= main-client.cpp
SERVER_NAME  	= server.cpp 
CLIENT_NAME  	= client.cpp
EXE_C_N		= client
EXE_S_N		= server
PARSER 	= ./parser/parser.cpp
COMMAND = ./command/command.cpp
DATABASE = ./DataBase/DataBase.cpp

all :
	${CC} ${SERVER_MAIN_NAME}  ${SERVER_NAME} ${COMMAND} ${DATABASE} ${PARSER} ${GET_EXE_NAME} ${EXE_S_N} ${THREADFLAG}
	${CC} ${CLIENT_MAIN_NAME} ${CLIENT_NAME} ${GET_EXE_NAME} ${EXE_C_N}
