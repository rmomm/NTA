FROM gcc:latest

WORKDIR /app
COPY . .

RUN g++ -o factorize main.cpp primality.cpp factorization.cpp

ENTRYPOINT ["./factorize"]