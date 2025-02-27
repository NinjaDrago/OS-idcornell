# Use the official GCC image
FROM gcc:latest

# Set the working directory inside the container
WORKDIR /app

# Copy the C source file to the container
COPY game.c .

# Compile the C program
RUN gcc -o game game.c

# Set the command to run the compiled program
CMD ["./game"]
