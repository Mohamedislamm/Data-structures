GRADE_POINTS = {
    'A+': 4.0, 'A': 3.7, 'B+': 3.3, 'B': 3.0,
    'C+': 2.7, 'C': 2.4, 'D+': 2.2, 'D': 2.0, 'F': 0.0
}

def get_user_input():
    print("Paste your course data below (press Enter twice to finish):")
    print("Format: CourseCode\ CourseName\Credits\Grade\\")
    
    lines = []
    while True:
        try:
            line = input()
            if line == "" and lines and lines[-1] == "":
                break
            lines.append(line)
            print(f"\rLines entered: {len(lines)}", end="", flush=True)
        except KeyboardInterrupt:
            print("\nInput cancelled. Restarting...")
            return None
    
    print("\nProcessing input...")
    return '\n'.join(lines)

def extract_course_data(text):
    if not text:
        return []
    
    lines = [line.strip() for line in text.split('\n') if line.strip()]
    courses = []
    i = 0
    
    while i < len(lines):
        line = lines[i]
        if (len(line) >= 4 and line[:2].isalpha() and 
            line[2:].isdigit() and 100 <= int(line[2:]) <= 999):
            
            course = {
                'code': line,
                'name': lines[i+1] if i+1 < len(lines) else "Unknown",
                'credits': lines[i+2] if i+2 < len(lines) else "0",
                'grade': None
            }
            
            for j in range(i+3, min(i+6, len(lines))):
                if lines[j] in GRADE_POINTS:
                    course['grade'] = lines[j]
                    break
            
            if course['grade']:
                courses.append(course)
                i = j + 1
            else:
                i += 1
        else:
            i += 1
    
    return courses

def calculate_gpa():
    previous_input_hash = None
    
    while True:
        text = get_user_input()
        if text is None:
            continue
        
        current_hash = hash(text)
        if current_hash == previous_input_hash:
            print("\nSame input detected. Did you mean to change something?")
            if input("Calculate again? (y/n): ").lower() != 'y':
                break
            continue
        
        previous_input_hash = current_hash
        courses = extract_course_data(text)
        
        if not courses:
            print("No valid courses found. Please check your input format.")
            continue
        
        total_quality = 0
        total_attempted = 0
        total_earned = 0
        
        print("\nCourse Summary:")
        print("-" * 60)
        print(f"{'Code':<8}{'Name':<30}{'Credits':>8}{'Grade':>8}{'Points':>8}")
        print("-" * 60)
        
        for course in courses:
            try:
                credits = int(course['credits'])
                grade = course['grade']
                points = GRADE_POINTS.get(grade, 0)
                quality = credits * points
                
                total_quality += quality
                total_attempted += credits
                if grade != 'F':
                    total_earned += credits
                
                name = (course['name'][:27] + '..') if len(course['name']) > 29 else course['name']
                print(f"{course['code']:<8}{name:<30}{credits:>8}{grade:>8}{quality:>8.1f}")
            except (ValueError, KeyError, TypeError) as e:
                print(f"Skipping invalid course entry: {course.get('code', 'Unknown')} - {str(e)}")
                continue
        
        if total_attempted > 0:
            gpa = total_quality / total_attempted
        else:
            gpa = 0.0
        
        print("\nResults:")
        print(f"Attempted Credits: {total_attempted}")
        print(f"Earned Credits: {total_earned}")
        print(f"Total Quality Points: {total_quality:.1f}")
        print(f"GPA: {gpa:.3f}")
        
        if input("\nCalculate another set? (y/n): ").lower() != 'y':
            break

if __name__ == "__main__":
    print("GPA Calculator (Ctrl+C to exit)")
    try:
        calculate_gpa()
    except KeyboardInterrupt:
        print("\nProgram exited.")