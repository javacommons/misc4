#lang racket
(require javascript)
(eval-script "print(40 + 2)")
(require pprint)
(pretty-print
 (format-term
  (parse-source-element
   "while (true) { print('break!'); break }")))

