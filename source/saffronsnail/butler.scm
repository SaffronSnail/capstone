(define-module (saffronsnail butler)
               #:export (run-butler-listener)
               #:use-module (saffronsnail attendant)
               #:use-module (saffronsnail butler glue)
               #:use-module (saffronsnail log)
)

; this is the 'main' of this file; it waits for someone to connect, reads the
; attendant request, and migrates the connection to a different port so that
; it can continue listening; there is currently no 'clean' way to close this,
; just ctrl-c at the terminal
(define* (run-butler-listener #:key (send-port 8080) (recv-port 8081)
                              (run-continuous? #t)
         )
  (entrance-protocol (receive-entrance-request recv-port) send-port)
  (if run-continuous?
    (begin (logmsg "continuing the butler listener")
           (run-butler-listener #:send-port send-port #:recv-port recv-port
                                #:run-continuous #t
           )
    )
    (logmsg "ending the butler listner")
  )
)

; the entrance protocol defines what happens when a user first makes contact
; with butler; it involves determining what attendant should serve this
; connection and what port the user will be speaking to for the rest of the
; connection
(define (entrance-protocol entrance-request send-port)
  (logmsg (string-append "Got a connection! Attendant requested: "
                         (attendant-name entrance-request)
          )
  )

  (let ((attendant (make-attendant entrance-request)))
    (logmsg "starting the attendant")
    (call-with-new-thread (lambda () (attendant 'start)))
    (logmsg "sleeping")
    (sleep 1)
    (logmsg "sending entrance response")
    (send-entrance-response send-port entrance-request (attendant 'port))
  )
)

(use-modules (saffronsnail butler test))
(run-tests)

