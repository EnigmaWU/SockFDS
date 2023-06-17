# SockFDS
* Add a new syscall, named 'sendfds', with args 'int fds[], int nfd, void *buf, size_t but_len' 
    * Use this syscall to send single buf of buf_len to multi sockfds
        * With shared socket buffer in linux kernel.

 
