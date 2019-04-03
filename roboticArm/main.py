import math

def degree_to_radian(angle):
    return angle * (math.pi / 180)

class Arm():
    def __init__(self):
        self.distance_base_to_roi=17
        self.degrees_distance_base_to_roi=55
        self.x_base=0.0
        self.y_base=0.0
        self.base_height=5.0
        self.shoulder_elbow=15
        self.elbow_hand=15
        self.height_top_piece = 2
        self.base_side=9
        self.radians_distance_base_to_roi=degree_to_radian(self.degrees_distance_base_to_roi)
        self.base_center=math.sqrt(math.pow(self.base_side, 2)+math.pow(self.base_side, 2))/2
        self.hypotenuse_to_center=math.sqrt(math.pow(self.base_center,2)+math.pow(distance_base_to_roi,2))
        self.radians_to_center=math.asin(self.base_center/self.hypotenuse_to_center)
        self.missing_radians=(math.pi/2)-(radians_to_center+radians_distance_base_to_roi)
        self.diff_x=math.sin(missing_radians)*hypotenuse_to_center
        self.diff_y=math.cos(missing_radians)*hypotenuse_to_center
      
    def move_to(self,y,x):
        plain_distance = math.sqrt(math.pow((y-self.y_base), 2)+math.pow((x-self.x_base), 2))
        base_angle = math.asin((y-self.y_base)/plain_distance)
        # move shoulder to angle in base reference
        rect_side=self.base_height - self.height_top_piece
        hypotenuse_side = math.sqrt(math.pow(rect_side,2)+math.pow(plain_distance, 2))
        cosA=(math.pow(self.shoulder_elbow,2)+ math.pow(hypotenuse_side, 2)- math.pow(self.elbow_hand, 2))/(2*self.shoulder_elbow*hypotenuse_side)
        tiltShoulderAngle = math.acos(cosA)
        # move tilt shouder
        cosC=(math.pow(self.elbow_hand,2)+ math.pow(self.shoulder_elbow, 2)- math.pow(hypotenuse_side, 2))/(2*self.elbow_hand*self.shoulder_elbow)
        tiltElbowAngle = math.acos(cosC)
        # move tiltElbowAngle

    def home(self):
        pass
    
    def close_pawn(self):
        pass

    def open_pawn(self):
        pass
    def set_base_agle(self, rad):
        pass
    
    def set_tiltin_angle_base(self, rad):
        pass

    def set_elbow_angle(self, rad):
        pass
    

def take_photo():
    pass

def process_photo():
    pass

import cv2
import numpy as np

def main():
    img = cv2.imread("shapes.png", cv2.IMREAD_GRAYSCALE)
    threshold = cv2.threshold(img, 240, 255, cv2.THRESH_BINARY)
    contours= cv2.findContours(threshold, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    
    font = cv2.FONT_HERSHEY_COMPLEX
    
    for cnt in contours:
        approx = cv2.approxPolyDP(cnt, 0.01*cv2.arcLength(cnt, True), True)
        cv2.drawContours(img, [approx], 0, (0), 5)
        x = approx.ravel()[0]
        y = approx.ravel()[1]
    
        if len(approx) == 3:
            cv2.putText(img, "Triangle", (x, y), font, 1, (0))
        elif len(approx) == 4:
            cv2.putText(img, "Rectangle", (x, y), font, 1, (0))
        elif len(approx) == 5:
            cv2.putText(img, "Pentagon", (x, y), font, 1, (0))
        elif 6 < len(approx) < 15:
            cv2.putText(img, "Ellipse", (x, y), font, 1, (0))
        else:
            cv2.putText(img, "Circle", (x, y), font, 1, (0))
    
    cv2.imshow("shapes", img)
    cv2.imshow("Threshold", threshold)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()