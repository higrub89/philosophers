# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhiguita <rhiguita@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/11 16:04:17 by rhiguita          #+#    #+#              #
#    Updated: 2026/09/22 17:30:30 by rhiguita         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SUBDIR      := philo

all:
	@$(MAKE) -C $(SUBDIR) all

clean:
	@$(MAKE) -C $(SUBDIR) clean

fclean:
	@$(MAKE) -C $(SUBDIR) fclean

re:
	@$(MAKE) -C $(SUBDIR) re

tsan:
	@$(MAKE) -C $(SUBDIR) tsan

debug:
	@$(MAKE) -C $(SUBDIR) debug

test: all
	@./tester/tester.sh .

.PHONY: all clean fclean re tsan debug test
