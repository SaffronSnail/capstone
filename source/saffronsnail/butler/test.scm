(define-module (saffronsnail butler test)
               #:use-module (saffronsnail butler)
               #:use-module (saffronsnail butler glue)

               #:use-module (srfi srfi-64)
)

(define config
  (alist->hash-table '((listener-port . 8080)
                       (payload-port . 8081)
                      )
  )
)

(let ((test-name "Entrance Protocol Tests"))
  (test-begin test-name)
  (call-with-new-thread (lambda () (run-butler-listener 8080)))
  (send-entrance-request 
  (test-end-test-name)
)

