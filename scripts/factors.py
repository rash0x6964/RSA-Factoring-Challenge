import sys

def factorize(n):
	for i in range(2, n // 2 + 1):
		if n % i == 0:
			return i, n // i
	return None

def main(file_path):
	with open(file_path, 'r') as file:
		for line in file:
			num = int(line.strip())
			factors = factorize(num)
			if factors:
				print(f"{num}={factors[1]}*{factors[0]}")

if __name__ == "__main__":
	if len(sys.argv) != 2:
		print("Usage: factors <file>", file=sys.stderr)
		sys.exit(1)

	file_path = sys.argv[1]
	main(file_path)
