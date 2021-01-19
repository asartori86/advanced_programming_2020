def reverse_dict(d):
    pass


def test_reverse_small_dict():
    d  = {"a": [1, 2, 3], "b": [45, 6], "c": [2, 45]}

    rd = {1: ["a"], 2: ["a", "c"], 3: ["a"], 6: ["b"], 45: ["b", "c"]}

    rd = reverse_dict(d)

    assert len(rd) == 5

    assert 'a' in rd[1]
    assert len(rd[1]) == 1

    assert 99 not in rd
    
    assert 'a' in rd[2]
    assert 'c' in rd[2]
    assert len(rd[2]) == 2
    
    assert 'a' in rd[3]
    assert len(rd[3]) == 1

    assert 'b' in rd[6]
    assert len(rd[6]) == 1

    assert 'b' in rd[45]
    assert 'c' in rd[45]
    assert len(rd[45]) == 2


import pytest

@pytest.fixture
def big_dict():
    chars = "qwertyuiopasdfghjklzxcvbnm"
    chars = sorted(chars.upper() + chars)

    keys = [c + str(n) for c in chars for n in range(100)]

    import random

    random.seed(42)

    d = {k: [random.randint(1, 200) for _ in range(random.randint(1, 10))] for k in keys}
    return d
    

def test_reverse_big_dict(big_dict):

    rd = reverse_dict(big_dict)

    assert 'A24' in rd[1]
    assert 'A25' not in rd[1]
    assert 'K10' in rd[77]
    assert len(rd) == 200
    assert len(rd[42]) == 150
    assert len(rd[147]) == 173
    assert len(rd[149]) == 115
    assert min([len(x) for x in rd.values()]) == 106
