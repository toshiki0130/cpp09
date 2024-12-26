NAME = btc

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic

SRCDIR = src
SRCS = $(wildcard $(SRCDIR)/*.cpp)

INCLUDES = $(wildcard $(SRCDIR)/*.hpp)
OBJDIR = obj
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $^ $(CXXFLAGS) -c -o $@

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all


.PHONY: all clean fclean re run format debug leakcheck
