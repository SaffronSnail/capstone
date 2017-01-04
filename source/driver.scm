#! /bin/guile \
-e main -s
!#

(add-to-load-path (dirname (current-filename)))
(use-modules (saffronsnail butler)
             (ice-9 getopt-long)
)

(define (main args)
  (define option-spec
    '((port (single-char #\p) (value #t)))
  )
  (define options (getopt-long (command-line) option-spec))
  (let ((port (option-ref options 'port #f)))
    (if port
      (run-butler-listener port)
      (run-butler-listener)
    )
  )
)

