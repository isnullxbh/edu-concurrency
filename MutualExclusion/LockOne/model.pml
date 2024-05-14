bool flags[2];
byte counter;

active [2] proctype user()
{
    assert(_pid == 0 || _pid == 1);

again:
    flags[_pid] = 1;
    (flags[1 - _pid] == 0);

    counter++;
    assert(counter == 1);
    counter--;

    flags[_pid] = 0;
    goto again
}
