FROM ubuntu:latest

RUN apt-get update
RUN apt-get install -y gcc
RUN apt-get install -y make
RUN apt-get install -y valgrind
RUN apt-get install -y libreadline-dev

# Clean up package cache to reduce image size
RUN apt-get clean && rm -rf /var/lib/apt/lists/*

# Set the working directory to /mnt
WORKDIR /mnt

# Commands to build the Docker image and run a container:
#   docker build -t ubuntu_valgrind .
#   docker run -it --name ubuntu_valgrind -v /Users/mott/42:/mnt ubuntu_valgrind
#   docker start ubuntu_valgrind
#   docker stop ubuntu_valgrind

# Command to run Valgrind for memory debugging:
# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./minishell
# valgrind --suppressions=suppressions.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./minishell
#   valgrind
# --leak-check=full
# --show-leak-kinds=all
# --track-origins=yes
# --track-fds=yes
