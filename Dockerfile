FROM alpine:latest
RUN apk upgrade &&\
    apk add build-base &&\
    apk add cmake &&\ 
    apk add bash