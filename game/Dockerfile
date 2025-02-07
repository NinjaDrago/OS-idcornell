# Use the official GCC image
FROM gcc:latest

# Install essential system libraries (including sys/wait.h)
RUN apt-get update && apt-get install -y build-essential

# Set the working directory inside the container
WORKDIR /app

# Copy the game source code into the container
COPY game.c .

# Compile the C program
RUN gcc -o game game.c

# Run the compiled program when the container starts
CMD ["./game"]
