NAME    =   Bank_1.a

CC      =   g++

CFLAGS  =   -std=c++11

RM      =   rm -f

ARCHV   =   ar crs

MAN_FUNC    =   show_client_list.cpp 		Add_Clients.cpp 		Find_client.cpp 		Delet_clients.cpp 		update_client.cpp		Bank_1_Project.cpp 

OBJ_FUNC    =   $(MAN_FUNC:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJ_FUNC)
	@$(ARCHV) $(NAME) $(OBJ_FUNC)

%.o : %.cpp Bank_1.hpp
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	@$(RM) $(OBJ_FUNC)

fclean : clean
	@$(RM) $(NAME)

re : fclean all

.PHONY : clean fclean re