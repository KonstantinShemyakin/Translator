const int const_int1 = 1;

float add(float arg1, float arg2);

void void_function();

int main()
{
    double d;
    d = 3.0;

    if (d < add(1, 2))
        d = 1;
    else
	d = -1;

    const int size = 5;
    int int_array[] = {1, 2, 3, 4, 5};
    int accum = 0;

    for (int i = 0; i < size; ++i)
        accum += int_array[i];

    accum *= d;   

    return 0;
}

float add(float arg1, float arg2)
{
    return arg1 + arg2;
}
