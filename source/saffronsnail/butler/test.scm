(define-module (saffronsnail butler test)
               #:export     (default-config run-tests)
               #:use-module (saffronsnail butler)
               #:use-module (saffronsnail butler glue)
               #:use-module (saffronsnail log)

               #:use-module (ice-9 hash-table)
               #:use-module (srfi srfi-64)
)

(define default-config
  (alist->hash-table '((request-listener-port  . 8080)
                       (request-sender-port    . 8081)
                       (response-listener-port . 8082)
                       (response-sender-port   . 8083)
                      )
  )
)

(define localhost "127.0.0.1")

(define* (run-tests #:key (config default-config))
  (let ((test-name "Entrance Protocol Tests")
        (lookup (lambda (symbol) (hash-ref config symbol)))
       )
    (logmsg (string-append "beginning test " test-name))
    (test-begin test-name)
  
    (logmsg "calling with new thread")
    (let ((other-thread (call-with-new-thread (lambda ()
            (run-butler-listener #:send-port (lookup 'response-sender-port)
                                 #:recv-port (lookup 'request-listener-port)
                                 #:run-continuous? #f
            )
         ))))

      (logmsg "sleeping")
      (sleep 1)
  
      (logmsg "sending entrance request")
      (send-entrance-request (lookup 'request-sender-port)
                             localhost (lookup 'request-listener-port)
                             "dummy"   (lookup 'response-listener-port)
      )

      (logmsg "sleeping")
      (sleep 1)

      (logmsg "receiving response")
      (test-eqv 0 (port (receive-entrance-response
                          (lookup 'response-listener-port)
                        )
                  )
      )

      (logmsg "joining the other thread...")
      (join-thread other-thread)
      (logmsg "joined")

      (logmsg (string-append "ending test " test-name))
      (test-end test-name)
    )
  )
)

