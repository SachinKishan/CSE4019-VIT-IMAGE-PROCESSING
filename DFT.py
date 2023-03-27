import numpy as np

# Define the basis matrix
Basis = np.array([
            [1, 1, 1, 1],
            [1, -1j, -1, 1j],
            [1, -1, 1, -1],
            [1, -1j, -1, 1j]
            ])

# Enter your input image
Input_Image = np.zeros((4, 4))

# Take input for each element of the array using a nested loop
for i in range(4):
    for j in range(4):
        Input_Image[i, j] = float(input(f"1Enter value for element ({i}, {j}): "))

# Print the final array
print("\nInput Matrix:\n", Input_Image)

# Compute the forward DFT using the formula:
# DFT = 1/N [Basis x Image x Basis]
DFT = (1/4) * np.matmul(np.matmul(Basis, Input_Image), Basis)

# Compute the inverse DFT using the formula:
# IDFT = 1/N [Basis*T x Transformed Image x Basis*T]
IDFT = (1/4) * np.matmul(np.matmul(np.conjugate(np.transpose(Basis)), DFT), np.conjugate(np.transpose(Basis)))

# Print output matrices
print("\nForward DFT:\n", DFT)
print("\n\nInverse DFT:\n", IDFT)
print("\n")
