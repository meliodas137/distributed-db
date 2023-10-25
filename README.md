# distributed-db
A distributed database, complete with serializable snapshot isolation, replication, and failure recovery.

## Steps to build and mount to Docker Env
1. docker build ./ -t distributed-db:latest
2. docker run -it --name distributed-db --privileged --rm -v "<path_to_repo>:/distributed-db" -w /distributed-db distributed-db /bin/bash

