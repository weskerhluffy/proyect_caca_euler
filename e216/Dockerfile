FROM gcc:4.9
COPY . /usr/src/myapp
WORKDIR /usr/src/myapp
RUN gcc -g3 -std=gnu99 main.c -o e216 -lm
ENV STDIN /Users/ernestoalvarado/eworkspace/proyect_euler/src/pc/in21.txt
CMD ["./a.sh"]
