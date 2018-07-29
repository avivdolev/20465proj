docker run -v "$(pwd)":/code/ -it --cap-add=SYS_PTRACE --security-opt seccomp=unconfined --name uni --rm uni/ubu
