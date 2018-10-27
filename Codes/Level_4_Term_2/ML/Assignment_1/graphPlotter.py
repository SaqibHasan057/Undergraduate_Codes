from matplotlib import pyplot as plt
import numpy as np

x = [5,10,20,30]
y1 = [0.8611872196494659,0.8622891649425238,0.8604761382129045,0.863442305675037]
y2 = [0.8589757412398921,0.8589757412398923,0.8589757412398921,0.8618867924528301]

plt.plot(x,y1,color='blue',label='F1 Score')
plt.plot(x,y2,color='red',label='Accuracy')
plt.legend()
plt.show()