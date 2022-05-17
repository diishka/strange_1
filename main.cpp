import cv2
import mediapipe as mp
import time
import math

mp_drawing = mp.solutions.drawing_utils
mp_drawing_styles = mp.solutions.drawing_styles
mp_hands = mp.solutions.hands

# x_min = hand_landmarks.landmark[0].x
# y_min = hand_landmarks.landmark[0].y


# def is_round():
#     pass

n = 0
k = 0
hand_mass = []


# len


def check_straight(hand, dir_hand):
    x_5 = hand.landmark[5].x
    y_5 = hand.landmark[5].y
    y_6 = hand.landmark[6].y
    y_7 = hand.landmark[7].y
    x_8 = hand.landmark[8].x
    y_8 = hand.landmark[8].y
    # 14-16-18-20
    if -y_8 + y_6 > 0 and -hand.landmark[12].y + hand.landmark[10].y > 0 and \
            hand.landmark[14].y - hand.landmark[16].y < 0 and hand.landmark[18].y - hand.landmark[20].y < 0:
        # print(dir_hand[0].classification[0])
        return True
    else:
        return False

    # print("==========x=5: " , hand.landmark[5].x)
    # print("==========y=5: " , hand.landmark[5].y)
    # print("==========x=8: " , hand.landmark[8].x)
    # print("==========y=8: " , hand.landmark[8].y)


# For webcam input:

x_min = 0
y_min = 0
y_max = 0
x_max = 0

cap = cv2.VideoCapture(0)

with mp_hands.Hands(
        model_complexity=0,
        max_num_hands=2,
        min_detection_confidence=0.7,
        min_tracking_confidence=0.5) as hands:
    while cap.isOpened():
        success, image = cap.read()

        if not success:
            print("Ignoring empty camera frame.")
            # If loading a video, use 'break' instead of 'continue'.
            continue

        # To improve performance, optionally mark the image as not writeable to
        # pass by reference.
        image.flags.writeable = False
        image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        results = hands.process(image)

        # Draw the hand annotations on the image.
        image.flags.writeable = True
        image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)

        if results.multi_hand_landmarks:
            # print(results.multi_handedness)
            for hand_landmarks in results.multi_hand_landmarks:
                mp_drawing.draw_landmarks(
                    image,
                    hand_landmarks,
                    mp_hands.HAND_CONNECTIONS,
                    mp_drawing_styles.get_default_hand_landmarks_style(),
                    mp_drawing_styles.get_default_hand_connections_style())
                # print(hand_landmarks.landmark[5].x)

                # check_straight(hand_landmarks, results.multi_handedness)

                # код diishka (я ничего не понимаю, вообще ничего)
                # я не знаю что я сделал.
                # не переживай брат
                # check_straight(hand_landmarks, results.multi_handedness)
                # print("x_min = ", x_min)
                # print("y_min = ", y_min)
                d = check_straight(hand_landmarks, results.multi_handedness)
                print("==========================")
                print(hand_landmarks.landmark[5].y)
                print(hand_landmarks.landmark[5].x)
                print("==========================")
                print("y ", hand_landmarks.landmark[6].y)
                print("x", hand_landmarks.landmark[6].x)
                print("==========================")

                # if d:
                # print(results.multi_handedness[0].classification[0].label)
                if n < 1:
                    y_prev = hand_landmarks.landmark[5].y
                    y_start = hand_landmarks.landmark[5].y
                    x_prev = hand_landmarks.landmark[5].x
                    x_start = hand_landmarks.landmark[5].x
                    n += 1
                    hand_mass.append((hand_landmarks.landmark[5].x, hand_landmarks.landmark[5].y))
                    print(hand_mass)
                    print(type(hand_mass))

                s = math.sqrt(abs(math.pow(hand_landmarks.landmark[5].x - hand_mass[-1][0], 2) + math.pow(hand_landmarks.landmark[5].y - hand_mass[-1][1], 2)))
                print(s)
                if (abs(hand_mass[0][0] - x_prev))>0.1:
                    hand_mass.append((hand_landmarks.landmark[5].x, hand_landmarks.landmark[5].y))


                '''
                        if x_prev > hand_landmarks.landmark[5].x and k == 0:
                            x_max = x_prev
                        else:
                            x_prev = hand_landmarks.landmark[5].x
    
                        if x_prev < hand_landmarks.landmark[5].x and k == 0:
                            x_min = x_prev
                        else:
                            x_prev = hand_landmarks.landmark[5].x
    
                        if y_prev < hand_landmarks.landmark[5].y:
                            y_min = y_prev
                        else:
                            y_prev = hand_landmarks.landmark[5].y
    
                        if y_prev > hand_landmarks.landmark[5].y:
                            y_max = y_prev
                            if y_max < y_prev:
                                pass
    
                            # if x_prev > hand_landmarks.landmark[0].x:
                            #     x_min = hand_landmarks.landmark[0].x
                            #
                            # else:
                            #     x_prev = hand_landmarks.landmark[0].x
    
                        else:
                            y_prev = hand_landmarks.landmark[5].y
                            # if x_min != 0 and x_prev > hand_landmarks.landmark[0].x:
                            #     y_min = hand_landmarks.landmark[0].y
    
                        # if y_prev > hand_landmarks.landmark[0].y:
                        #     y_max = y_prev
                        #     if x_prev > hand_landmarks.landmarks[0].x:
                        #         x_min = hand_landmarks.landmarks[0].x
                        #
                        #     else:
                        #         x_prev = hand_landmarks.landmarks[0].x
                        #
                        # else:
                        #     y_prev = hand_landmarks.landmark[0].y
                        #     if x_min != 0 and x_prev > hand_landmarks.landmarks[0].x:
                        #         y_min = hand_landmarks.landmarks[0].y
                        #         if hand_landmarks.landmarks[0].y - y_n < 0 and hand_landmarks.landmarks[0].x - x_n > 0:
                        #             break
                        print("=================")
                        print("x_min ", x_min)
                        print("y_min ", y_min)
                        print("y_max ", y_max)
                        print("x_max ", x_max)
                        print("=================")
                        '''
                # конец кода diishka он лал

        # Flip the image horizontally for a selfie-view display.
        # print(results.multi_hand_landmarks)

        cv2.imshow('MediaPipe Hands', cv2.flip(image, 1))
        cv2.waitKey(30)
        # if cv2.waitKey() & 0xFF == 48:
        #     break

cap.release()
