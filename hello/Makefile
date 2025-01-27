build: Dockerfile hello.cpp
	docker build -t cpp-hello-world . && touch build
run: build
	docker run --rm cpp-hello-world
clean:
	docker rmi cpp-hello-world && rm build
CHAT=https://chatgpt.com/share/67980bd8-ec84-8013-ab96-e090885022f9
chat:
	@if [ "$(OS)" = "Windows_NT" ]; then \
		start $(CHAT); \
	elif command -v xdg-open > /dev/null; then \
		xdg-open $(CHAT); \
	else \
		open $(CHAT); \
	fi