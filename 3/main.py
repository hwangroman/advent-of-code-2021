from functools import reduce
from operator import add

def main():
    #file = open("input_small.txt")
    file = open("input.txt")

    # transform each line to work set tuple
    # each element is integer bit and count accumulator.
    # tuple(
    #   tuple(
    #     int bit,
    #     int count_acc
    #   )   
    # )
    # for instance, "01111" -> ((1, 1) (0, 1), (1, 1), (1, 1), (1, 1), (1, 1))
    ws = map(
        lambda line: 
                tuple(
                    map(
                        # maps each bit to integer
                        lambda char: (int(char), 1), 
                        line[:-1]
                    )
                ),
        file
    )

    ws = tuple(ws)
    print("Working Set:")
    for w in ws:
        print (w)

    # Reduce the work set into component-wise sum elements.
    # Resulting data:
    # tuple(
    #   tuple(
    #     int oneCount,
    #     int totalCount
    #   )
    # )
    reduced = reduce(
        lambda a, b: 
            map(
                lambda x, y: map(add, x, y), 
                a, 
                b
            ),
        ws
    )

    reduced = map(lambda x: tuple(x), reduced)
    reduced = tuple(reduced)
    print("Reduced:")
    print(tuple(reduced))

    # Get gamma by dividing each element by count and rounding up to int
    gamma = tuple(map(lambda x: int(x[0]/x[1] + 0.5), reduced))
    print("Gamma", gamma)

    # Transform into gamma tuple with power of 2:
    # tuple(
    #   tuple(
    #     int bit, 
    #     int powerOfTwo
    #   )
    # )
    res = map(
        lambda x: (x[0], pow(2, len(gamma) - x[1] - 1)),
        ((x, i) for i, x in enumerate(gamma))
    )

    # Accumulate sum of power of twos into dictionary {0: N, 1: M}
    # N is sum of power of two for 0 bits
    # M is sum of power of two for 1 bits
    res = reduce(
            lambda acc, e: acc.update({e[0]: acc[e[0]] + e[1]}) or acc, 
            res, 
            {0: 0, 1: 0}
        )

    # Multiple the values together.
    res = reduce(
        lambda a, b: a * b, 
        res.values()
    )
    print("Result", res)

    file.close()

if __name__ == "__main__":
    main()