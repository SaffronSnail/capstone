(define-module (saffronsnail attendant)
               #:export (make-attendant)
               #:use-module (system foreign)
)

(define (create-load-func ret func-name args)
  (lambda (lib)
    (pointer->procedure ret (dynamic-func func-name lib) args)
  )
)

(define load-init (create-load-func '* "init" '(* *)))
(define load-start (create-load-func void "start" '()))
(define load-validate (create-load-func int "validate_data"
                                        '(* *)
                      )
)
(define load-transform-incoming (create-load-func '* "transform_incoming_data"
                                                  '(* *)
                                )
)
(define load-transform-outgoing (create-load-func '* "transform_outgoing_data"
                                                  '(* *)
                                )
)
(define load-stop (create-load-func void "stop" '(*)))

(define (make-attendant attendant-name entrance-request)
  ; TODO: load the library
  (let* ((lib (dynamic-link (string "/lib/attendants/" attendant-name)))

         (validate           (load-validate           lib))
         (transform-incoming (load-transform-incoming lib))
         (transform-outgoing (load-transform-outgoing lib))

         (send-data (lambda (data) (display "fake sending data") (newline)))
         (wait-for-data (lambda () (display "fake waiting for data") (newline)))

         (attendant ((load-init lib) send-data wait-for-data)) 

         (start              (load-start              lib))
         (stop               (load-stop               lib))
        )

    ; this function dispatcher is an 'instance' of the attendant
    (lambda (func . args)
      (case func
        (('start) (start attendant (first args)))
        (('stop) (stop attendant))
        (('port) (warn "need to determine port number in make-attendant") 8081)

        ; I'm not sure we ever want to call these from scheme, but we might and
        ; we need to make sure that these functions don't get garbage-collected
        ; anyway, since we pass them to c code
        (('send-data) (send-data (first args)))
        (('wait-for-data) (wait-for-data))
      )
    )
  )
)

