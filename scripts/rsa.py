import sys

def is_prime(number):
	if number < 2:
		return False
	for i in range(2, int(number**0.5) + 1):
		if number % i == 0:
			return False
	return True

def factorize(n):
	for i in range(2, n // 2 + 1):
		if n % i == 0 and is_prime(i) and is_prime(n // i):
			return i, n // i
	return None

def process(file_path):
	with open(file_path, 'r') as file:
		for line in file:
			num = int(line)
			factors = factorize(num)
			if factors:
				print(f"{num}={factors[1]}*{factors[0]}")

if __name__ == "__main__":
	if len(sys.argv) != 2:
		print("Usage: factors <file>", file=sys.stderr)
		sys.exit(1)

	process(sys.argv[1])
