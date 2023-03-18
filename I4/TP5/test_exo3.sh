for n in tests_exo3/*
do
    echo "--- test $n ---"
    cat $n
    echo
    ./calculette $n
    ./test_lexeme $n
    echo
    echo
    echo
done