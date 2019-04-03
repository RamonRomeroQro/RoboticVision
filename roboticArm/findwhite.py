import numpy as np
import cv2

im_gray = cv2.imread('white.png', cv2.IMREAD_GRAYSCALE)
(thresh, im_bw) = cv2.threshold(im_gray, 128, 255, cv2.THRESH_BINARY | cv2.THRESH_OTSU)
kernel = np.ones((5,5),np.uint8)
dilation = cv2.dilate(im_bw,kernel,iterations = 2)
cv2.imshow('d',dilation)
contours,hierarchy = cv2.findContours(im_bw, 1, 2)
cnt = contours[0]
M = cv2.moments(cnt)
#print( M )
cx = int(M['m10']/M['m00'])
cy = int(M['m01']/M['m00'])
print(cx)
print(cy)

cv2.waitKey(0)
cv2.destroyAllWindows()