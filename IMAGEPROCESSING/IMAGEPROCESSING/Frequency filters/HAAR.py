import numpy as np

# Define the basis matrix
Basis = np.array([
            [0.5, 0.5, 0.5, 0.5],
 		    [0.5, 0.5, -0.5, -0.5],
 		    [0.707, -0.707, 0, 0],
 		    [0, 0, 0.707, -0.707]
            ])

# Enter your input image
Input_Image = np.zeros((4, 4))

# Take input for each element of the array using a nested loop
for i in range(4):
    for j in range(4):
        Input_Image[i, j] = float(input(f"Enter value for element ({i}, {j}): "))

# Print the final array
print("\nInput Matrix:\n", Input_Image)

# Compute the forward HAAR using the formula:
# HAAR = [Basis x Image x BasisT]
HAAR = np.matmul(np.matmul(Basis, Input_Image), np.transpose(Basis))

# Compute the inverse HAAR using the formula:
# HAAR = [BasisT x Transformed Image x Basis]
IHAAR = np.matmul(np.matmul(np.transpose(Basis), HAAR), Basis)

# Print output matrices
print("\nForward HAAR:\n", HAAR)
print("\n\nInverse HAAR:\n", IHAAR)
print("\n")