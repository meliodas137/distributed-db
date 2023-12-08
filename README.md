# distributed-db
A distributed database, complete with serializable snapshot isolation, replication, and failure recovery. The app is built completely from scratch and utilizes Multi-Versioning Read Consistency and Available Copies algorithm to achieve concurrency. Moreover, we utilise Serializable Snapshot Isolation to achieve lock free transaction commits.

## Steps to build and mount to Docker Environment
1. docker build ./ -t distributed-db:latest
2. docker run -it --name distributed-db --privileged --rm -v "<path_to_repo>:/distributed-db" -w /distributed-db distributed-db /bin/bash

**Note:** If you don't want to use docker environment, please make sure that the cmake version is greater than `3.11` (on CIMS server, use `module load cmake-3.22`).

## Steps to build and run the app
1. Run `make` from the root directory.
2. Run `./build/apps/DistributedDB`.
3. Input transaction commands starting from ``begin(T1)``.
4. There are test cases present in the `./test/` folder. To use a test case and see it's output, run: `./build/apps/DistributedDB < ./test/<test>.txt`
