import numpy as np

# Define the basis matrix
Basis = np.array([
            [0.5, 0.5, 0.5, 0.5],
 		    [0.65, 0.27, -0.27, -0.65],
 		    [0.5, -0.5, -0.5, 0.5],
 		    [0.27, -0.65, 0.65, -0.27]
            ])

# Enter your input image
Input_Image = np.zeros((4, 4))

# Take input for each element of the array using a nested loop
for i in range(4):
    for j in range(4):
        Input_Image[i, j] = float(input(f"Enter value for element ({i}, {j}): "))

# Print the final array
print("\nInput Matrix:\n", Input_Image)

# Compute the forward DCT using the formula:
# DCT = [Basis x Image x BasisT]
DCT = np.matmul(np.matmul(Basis, Input_Image), np.transpose(Basis))

# Compute the inverse DCT using the formula:
# IDCT = [BasisT x Transformed Image x Basis]
IDCT = np.matmul(np.matmul(np.transpose(Basis), DCT), Basis)

# Print output matrices
print("\nForward DCT:\n", DCT)
print("\n\nInverse DCT:\n", IDCT)
print("\n")
