(define-module (saffronsnail attendant)
               #:export (make-attendant)
               #:use-module (saffronsnail butler glue)
               #:use-module (saffronsnail log)

               #:use-module (system foreign)
)

; this is a metafunction which defines functions that load a specific function
; from a given library
(define (create-load-func ret func-name args)
  (lambda (lib)
    (pointer->procedure ret (dynamic-func func-name lib) args)
  )
)

; the following functions are helper functions for loading the callbacks from an
; attendant module
(define load-init (create-load-func '* "init" '(* *)))
(define load-start (create-load-func void "start" '()))
(define load-validate (create-load-func int "validate_data"
                                        '(* *)
                      ))
(define load-transform-incoming (create-load-func '* "transform_incoming_data"
                                                  '(* *)
                                )
)
(define load-transform-outgoing (create-load-func '* "transform_outgoing_data"
                                                  '(* *)
                                )
)
(define load-stop (create-load-func void "stop" '(*)))

; loads and intializes an attendant, but does NOT signal the attendant to begin
; communicating with the client
(define (make-attendant entrance-request)
  (let* ((lib (dynamic-link (string-append "lib"
                                           (attendant-name entrance-request))))

         (validate           (load-validate           lib))
         (transform-incoming (load-transform-incoming lib))
         (transform-outgoing (load-transform-outgoing lib))

         (send-data (lambda (data) (display "fake sending data") (newline)))
         (wait-for-data (lambda () (display "fake waiting for data") (newline)))

         (attendant ((load-init lib) (procedure->pointer void send-data '(*))
                                     (procedure->pointer '* wait-for-data '())
                    )
         )

         (start (load-start lib))
         (stop  (load-stop  lib))
        )

    ; this function dispatcher is an 'instance' of the attendant
    (lambda (func . args)
      (cond
        ((eq? 'start func) (start attendant (first args)))
                           
        ((eq? 'stop  func) (stop attendant))
        ((eq? 'port  func) (warn (string-append "need to determine port number"
                                                "in make-attendant"))
                                 0
        )

        ; I'm not sure we ever want to call these from scheme, but we might and
        ; we need to make sure that these functions don't get garbage-collected
        ; anyway, since we pass them as callbacks to c code
        ((eq? 'send-data func) (send-data (first args)))
        ((eq? 'wait-for-data func) (wait-for-data))
                                           
        (else (error (string-append "did not recognize request for function "
                                    (symbol->string func))
              )
        )
      )
    )
  )
)

