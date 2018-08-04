
# Matrix

Serve to define matrices and their basic operations, as well as using sheltongabe/json_util to save it easily.
Serves simply as a two-dimensional list that holds things.  Things are something that the operations of
addition with a matrix of equavilent dimension, multiplication by a scalar, or a Matrix fitting a certain rule,
is meaningful.

Technically, you can store anything, however if used in parallel with other libraries, it could cause undefined
behavior if those basic rules are not followed.

## Dependencies

> * [json_util](https://www.github.com/sheltongabe/json_util) (V0.5)
