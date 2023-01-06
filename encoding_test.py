import subprocess
import base64
import string
import random
import sys

def get_random_string(length):

    letters = string.ascii_lowercase + string.ascii_uppercase + string.digits
    return "".join(random.choice(letters) for _ in range(length))

def main():

    for i in range (1, 15):
        for x in range(250):
            print("\rtest input length: {} \t round: {}".format(i, x), end="")
            sys.stdout.flush()

            test_str = get_random_string(i)

            assertion = base64.b64encode(test_str.encode("utf-8")).decode("utf-8")

            result = subprocess.run(["./base", test_str], stdout=subprocess.PIPE)
            str_result = result.stdout.decode("utf-8")
            if str_result.strip() != assertion:
                print("ERROR. expect: {} to be: {}. got: {}".format(test_str, assertion, str_result))
                sys.exit(1)

    print("\n\n\nall good!")
    sys.exit(0)

if __name__ == "__main__":
    main()