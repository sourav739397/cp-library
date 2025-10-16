#!/bin/bash

# ==============================================
#  Professional Competitive Programming Script
# ==============================================
#  Features:
#  - Fast/Debug compilation modes
#  - Test case parsing from Competitive Companion
#  - Automated testing against samples
#  - Stress testing with generator/validator
#  - Multiple solutions checking
#  - Time/memory measurement
#  - Colorful output with emojis
#  - Comprehensive help system

# ================ CONFIGURATION ================
VERSION="1.1.0"
AUTHOR="sourav739397"
CONTACT="sourav739397@gmail.com"

# Global flags for compilation
FAST_COMPILE="g++ -fdiagnostics-color=always -std=c++23 -Wshadow -Wall -Wno-unused-result -O2 -o"
DEBUG_COMPILE="g++ -DLOCAL -fdiagnostics-color=always -std=c++23 -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -fsanitize=signed-integer-overflow -D_GLIBCXX_DEBUG -o"

# Default values
CMD=""
SOURCE_FILE=""
IS_PYTHON=false
RUN_ONLY=false
ADD_TESTCASE=false
TIMEOUT_DURATION=2  # seconds
COMPILE_SCRIPT="$FAST_COMPILE"

# Stress testing and validation defaults
WRONG_SOLUTION="sol.cpp"
SLOW_SOLUTION="slow.cpp"
VALIDATOR="validator.cpp" # multiple test case
GENERATOR="gen.cpp"
TEST_COUNT=10000  # Default stress test count

# Test case handling
SAMPLE_DIR="name"
INPUT_FILES=()
SPECIFIC_TESTS=()
MULTIPLE_SOLUTION=false

# ================ FUNCTIONS ====================

# Print colorful header
print_header() {
    echo -e "\033[1;34m"
    echo "╔══════════════════════════════════════════╗"
    echo "║    Competitive Programming Automation    ║"
    echo "║       Version $VERSION - $AUTHOR       ║"
    echo "╚══════════════════════════════════════════╝"
    echo -e "\033[0m"
}

# Show help menu
show_help() {
    print_header
    echo -e "\033[1;33mUsage:\033[0m"
    echo "  ./cphelper.sh [options] <source-file>"
    echo ""
    
    echo -e "\033[1;36mMain Options:\033[0m"
    echo -e "  \033[1m--help\033[0m          Show this help message"
    echo -e "  \033[1m--version\033[0m       Show version information"
    echo -e "  \033[1m--parse\033[0m [here|group] Parse problem from Competitive Companion"
    echo -e "  \033[1m--test\033[0m [indices] Test against sample cases (default: all)"
    echo -e "  \033[1m--stress\033[0m [args] Run stress testing"
    echo ""
    
    echo -e "\033[1;36mAdditional Flags:\033[0m"
    echo -e "  \033[1m-a\033[0m             Add a new test case manually"
    echo -e "  \033[1m-d\033[0m             Use debug compilation mode"
    echo -e "  \033[1m-r\033[0m             Run only (skip compilation)"
    echo -e "  \033[1m-m\033[0m             Enable multiple solution checking"
    echo ""
    
    echo -e "\033[1;36mStress Testing Arguments:\033[0m"
    echo -e "  Format: --stress <wrong solution> <brute force solution> <generator> <test-count>"
    echo -e "  Default: --stress sol.cpp judge.cpp gen.cpp 10000"
    echo ""
    
    echo -e "\033[1;35mExamples:\033[0m"
    echo -e "  \033[1mBasic:\033[0m ./cphelper.sh solution.cpp"
    echo -e "  \033[1mTesting:\033[0m ./cphelper.sh --test 1 2 solution.cpp"
    echo -e "  \033[1mStress:\033[0m ./cphelper.sh --stress -m wrong.cpp brute.cpp gen.cpp"
    echo ""
    echo -e "\033[1;37mReport issues to: $CONTACT\033[0m"
}

# Show version info
show_version() {
    print_header
    echo -e "\033[1;33mVersion:\033[0m $VERSION"
    echo -e "\033[1;33mAuthor:\033[0m $AUTHOR"
    echo -e "\033[1;33mFeatures:\033[0m"
    echo "  - C++23 support"
    echo "  - Python support"
    echo "  - Test case management"
    echo "  - Stress testing framework"
    echo "  - Competitive Companion integration"
}

# Check if value exists in array
contains() {
    local value="$1"
    for item in "${specific_tests[@]}"; do
        if [[ "$item" == "$value" ]]; then
            return 0
        fi
    done
    return 1
}

# Normalize output for comparison
normalize_output() {
    tr '[:upper:]' '[:lower:]' | tr -s ' ' | sed 's/[[:space:]]*$//' | awk 'NF {print}'
}

# Format time in human readable way
format_time() {
    local ms=$1
    if (( ms < 1000 )); then
        echo "${ms}ms"
    else
        echo "$((ms/1000)).$((ms%1000/100))s"
    fi
}

if [[ -f "./.testcases/time_limit.txt" ]]; then
    TIMEOUT_DURATION=$(< "./.testcases/time_limit.txt")
fi

# Parse problem from Competitive Companion
parse_problem() {
    local PORT=1327
    echo -e "\033[1;33m󰮏  Click the 'Parse Task (+)' button in your browser\033[0m"

    # Listen for data from Competitive Companion
    local data=$(nc -l -p "$PORT" | tr -d '\r' | sed '1,/^$/d' | jq -c '.' 2>/dev/null)

    if [ -z "$data" ]; then 
        echo -e "\033[1;31m  No valid data received\033[0m"
        return 1
    fi

    # Extract problem information
    local problem_name=$(echo "$data" | jq -r '.name')
    local contest_name=$(echo "$data" | jq -r '.group')
    local url=$(echo "$data" | jq -r '.url')
    local tests=$(echo "$data" | jq '.tests')
    local contest_number=$(echo "$url" | grep -oE '[0-9]+')

    local time_limit_ms=$(echo "$data" | jq -r '.timeLimit')
    local time_limit_sec=$(awk "BEGIN {printf \"%.3f\", $time_limit_ms/1000}")

    # Debug print (optional):
    echo -e "\033[1;34m  Time Limit: ${time_limit_sec} sec\033[0m"

    # Format names for filesystem
    contest_name=$(echo "$contest_name" | sed -E 's/^[^ ]+ - (.*)$/\1/' | sed 's/[^a-zA-Z0-9 ]//g' | tr ' ' '_')
    problem_name=$(echo "$problem_name" | sed 's/[^a-zA-Z0-9.]//g' | tr -d ' ')

    # Codeforces specific formatting
    if [[ "$contest_name" == *"Codeforces"* ]]; then 
        contest_name="CF$contest_number"
    fi    

    # Determine directory structure
    local dir="./.testcases"
    case "$sample_dir" in
        "name") dir="${problem_name}/.testcases" ;;
        "group") dir="${contest_name}/${problem_name}/.testcases" ;;
    esac
    
    # Create directory
    mkdir -p "$dir"
    echo "$time_limit_sec" > "${dir}/time_limit.txt"

    # clean old test cases
    rm -f "$dir"/sample*.{in,out}

    # Save test cases
    local index=1
    echo "$tests" | jq -c '.[]' | while read -r test; do
        local input=$(echo "$test" | jq -r '.input')
        local output=$(echo "$test" | jq -r '.output')

        echo "$input" > "${dir}/sample${index}.in"
        echo "$output" > "${dir}/sample${index}.out"
        echo -e "\033[0;37m󰄲  Saved sample${index}.in & sample${index}.out\033[0m"
        ((index++))
    done

    echo -e "\033[1;37m  All test cases saved for: $problem_name\033[0m"
    exit 0
}

# Add a new test case interactively
add_test_case() {
    local count=$(ls sample*.in 2>/dev/null | wc -l)
    local new_input="sample$((count + 1)).in"
    local new_output="sample$((count + 1)).out"
    
    echo -e "\033[0;36m  Enter input (Ctrl+D to finish):\033[0m"
    cat > "$new_input"
    
    echo -e "\033[0;36m  Enter expected output (Ctrl+D to finish):\033[0m"
    cat > "$new_output"
    
    echo -e "\033[1;37m  Test case added: $new_input & $new_output\033[0m"
}

# Print test case comparison side by side
print_comparison() {
    local expected="$1"
    local actual="$2"

    local expected_lines actual_lines max_file_lines
    expected_lines=$(wc -l < "$expected")
    actual_lines=$(wc -l < "$actual")
    max_file_lines=$(( expected_lines > actual_lines ? expected_lines : actual_lines ))

    echo -e "\033[4;36m  Comparison:\033[0m"
    line_num=1  # Start line numbering
    exec 3<"$expected" 4<"$actual"  # Open files for reading

    # Print the top border and column headers
    echo "┌────┬────────────────────────────────────┬────────────────────────────────────┐"
    echo -e  "│ L  │            \033[1;35mOutput\033[0m                  │              \033[1;33mExpected\033[0m              │"
    echo "└────┴────────────────────────────────────┴────────────────────────────────────┘"

    while (( line_num <= max_file_lines )); do
        read -r o_line <&3
        read -r a_line <&4

        # If one line is empty, print it as blank
        [[ -z "$o_line" ]] && o_line=" "  
        [[ -z "$a_line" ]] && a_line=" "

        # Apply colors to only the Output column
        if [[ "$o_line" == "$a_line" ]]; then
            # Green for matching lines in Output
            printf "│ %-2s │ \033[0;32m%-34s\033[0m │ %-34s │\n" "$line_num" "$a_line" "$o_line"
        else
            # Red for differing lines in Output
            printf "│ %-2s │ \033[0;31m%-34s\033[0m │ %-34s │\n" "$line_num" "$a_line" "$o_line"
        fi

        ((line_num++))  # Increment line number
    done

    # Print the bottom border
    echo "└────┴────────────────────────────────────┴────────────────────────────────────┘"
    exec 3<&- 4<&-  # Close file descriptors

}

# Compile a source file
compile_file() {
    local source_file=$1
    local executable=$2
    local compile_command=$3
    
    echo -e "\033[0;37m  Compiling $source_file....\033[0m"

    # Compile the source file
    $compile_command "$executable" "$source_file" &> compilation.log

    # Check for compilation errors
    if grep -q "error:" compilation.log; then
        echo -e "\033[1;31m  Compilation failed: $source_file\033[0m"
        cat compilation.log | grep "error:"
        rm -f compilation.log
        return 1
    fi

    # Check for warnings
    if grep -q "warning:" compilation.log; then
        echo -e "\033[1;33m  Compilation warning\033[0m"
        cat compilation.log | grep "warning:"
    fi
    rm -f compilation.log
    echo -e "\033[0;37m󰄲  Compilation successful: $source_file\033[0m"
    return 0
}

# Run test cases against solution
run_tests() {
    local executable=$1
    local is_py=$2
    local total_tests=0
    local passed_tests=0
    local failed_tests=0

    echo -ne "\033[0;37m  Checking sample tests\033[0m"
    # Dot animation while loading
    for i in {1..3}; do
        # echo -ne "."
        echo -ne "\033[0;37m.\033[0m"
        sleep 0.25
    done
    echo
    
    
    # for input_file in $(ls sample*.in 2>/dev/null | sort -V); do
    for input_file in $(ls ./.testcases/sample*.in 2>/dev/null | sort -V); do
        [[ -f "$input_file" ]] || continue
        
        local index="${input_file//[^0-9]/}"
        local output_file="${input_file%.in}.out"
        
        ((total_tests++))
        
        # Check if output file exists
        if [[ ! -f "$output_file" ]]; then
            echo -e "\033[1;31m  Missing output for test $index!\033[0m"
            ((failed_tests++))
            continue
        fi
        
        # Run the solution
        local start_time=$(date +%s%N)
        local timeout_cmd="timeout $TIMEOUT_DURATION"
        
        if (( is_py )); then
            $timeout_cmd python3 "$executable" < "$input_file" > output.out
        else
            $timeout_cmd ./"$executable" < "$input_file" > output.out
        fi
        
        local exit_code=$?
        local end_time=$(date +%s%N)
        local execution_time=$(((end_time - start_time) / 1000000))
        
        # Handle timeout
        if (( exit_code == 124 )); then
            echo -e "\033[1;37m󱫌  Sample Test #$index:\033[0m \033[1;33mTIME LIMIT EXCEEDED\033[0m (\033[0;33mTime: ${execution_time}ms\033[0m)"
            # echo -e "\033[1;37m  Test #$index:\033[0m \033[1;33mTIMEOUT\033[0m (>${TIMEOUT_DURATION}s)"
            ((failed_tests++))
            continue
        fi
        
        # Handle runtime errors
        if (( exit_code != 0 )); then
            echo -e "\033[1;37m  Test #$index:\033[0m \033[1;31mRUNTIME ERROR\033[0m"
            if [[ -s runtime.err ]]; then
                echo -e "\033[31m$(cat runtime.err)\033[0m"
            fi
            ((failed_tests++))
            continue
        fi
        
        # Handle multiple solutions
        if $MULTIPLE_SOLUTION; then
            if [[ ! -f "checker.cpp" ]]; then
                echo -e "\033[1;31m  Missing checker.cpp for multiple solutions!\033[0m"
                return 1
            fi
            
            if ! compile_file "checker.cpp" "checker" "$compile_script"; then
                return 1
            fi
            
            ./checker < output.out > temp_actual.out
            ./checker < "$output_file" > temp_expected.out
            output_file="temp_expected.out"
        fi
        
        # Compare outputs
        if cmp -s <(normalize_output < output.out) <(normalize_output < "$output_file"); then
            ((passed_tests++))
            echo -e "\033[1;37m󰄲  Sample Test #$index:\033[0m \033[1;32mACCEPTED\033[0m (\033[0;33mTime: ${execution_time}ms\033[0m)"
        else
            echo -e "\033[1;37m  Sample Test #$index:\033[0m \033[1;31mWRONG ANSWER\033[0m (\033[0;33mTime: ${execution_time}ms\033[0m)"
            echo -e "\033[4;36m  Input:\033[0m"
            cat  "$input_file"
            print_comparison "$output_file" "output.out"
            
        fi
    done
    
    # Cleanup
    rm -f output.out runtime.err temp_actual.out temp_expected.out checker 2>/dev/null
    
    echo -ne "\033[1;36m  Final Score: \033[0m"
    echo -e "\033[1;31m$((total_tests - passed_tests))\033[0m /\033[1;32m $passed_tests\033[0m / \033[1;37m$total_tests\033[0m"
    
    return $(( failed_tests > 0 ))
}

# Run stress testing
stress_test() {
    
    # Compile all required files
    if ! compile_file "$WRONG_SOLUTION" "wrong" "$COMPILE_SCRIPT"; then return 1; fi
    if ! compile_file "$SLOW_SOLUTION" "slow" "$COMPILE_SCRIPT"; then return 1; fi
    if ! compile_file "$GENERATOR" "generator" "$COMPILE_SCRIPT"; then return 1; fi

    # echo -ne "\033[0;37m  Running stress test\033[0m"
    # # Dot animation while loading
    # for i in {1..3}; do
    #     # echo -ne "."
    #     echo -ne "\033[0;37m.\033[0m"
    #     sleep 0.30
    # done
    # echo
    # Animation setup
    # Option 1: Braille spinner (original)
    # Unicode spinner frames (braille dots)
    # Some sample spinner frames:
    local anim_frames=('⠋' '⠙' '⠹' '⠸' '⠼' '⠴' '⠦' '⠧' '⠇' '⠏')  # Braille spinner
    # local anim_frames=('|' '/' '-' '\\')  # Classic spinner
    # local anim_frames=('◐' '◓' '◑' '◒')  # Circle spinner
    # local anim_frames=('▖' '▘' '▝' '▗')  # Quarter block spinner
    # local anim_frames=('⠁' '⠂' '⠄' '⡀' '⢀' '⠠' '⠐' '⠈')  # Dots spinner
    # local anim_frames=('O~~~~' '~O~~~' '~~O~~' '~~~O~' '~~~~O')  # Dots spinner
    # Pacman animation frames (for fun)
    # local anim_frames=('ᗧ···' 'ᗧ··' 'ᗧ·' 'ᗧ' 'C·' 'ᗤ·' 'ᗤ··' 'ᗤ···')
    # local anim_frames=('⠋~O~~~ ' '⠙' '⠹' '⠸' '⠼' '⠴' '⠦' '⠧' '⠇' '⠏')
    local anim_index=0
    local num_frames=${#anim_frames[@]}

    for ((testNum=1; testNum<=TEST_COUNT; testNum++)); do
        # Animation: print spinner and progress
        if (( testNum % 50 == 1 )); then  # Only update animation every 10 iterations
            anim_char="${anim_frames[anim_index]}"
            printf "\r\033[0;37m  Stress testing [%d/%d] %s\033[0m" "$testNum" "$TEST_COUNT" "$anim_char"
            anim_index=$(( (anim_index + 1) % num_frames ))
        fi
        # No sleep here, so only the animation is slowed, not the process itself

        # Generate test case
        ./generator > input
        ./slow < input > outSlow
        ./wrong < input > outWrong

        if ! cmp -s "outWrong" "outSlow"; then
            echo -e "\n\033[1;31m  Error found in test #$testNum!\033[0m"
            echo -e "\033[4;36m  Input:\033[0m"
            cat input
            print_comparison "outSlow" "outWrong"
            rm -f wrong judge generator input outSlow outWrong 2>/dev/null
            exit
        fi      
    done
    # Clear animation line after loop
    echo -ne "\r\033[K"
    echo -e "\033[1;32m󰄲  Passed $TEST_COUNT tests successfully!\033[0m"

    # Cleanup
    rm -f wrong judge generator input outSlow outWrong 2>/dev/null
}

# Validate solution against a validator
validation_test() {
    # Compile all required files
    if ! compile_file "$WRONG_SOLUTION" "wrong" "$COMPILE_SCRIPT"; then return 1; fi
    if ! compile_file "$VALIDATOR" "validator" "$COMPILE_SCRIPT"; then return 1; fi
    if ! compile_file "$GENERATOR" "generator" "$COMPILE_SCRIPT"; then return 1; fi

    echo -ne "\033[0;37m  Running validation test\033[0m"
    # Dot animation while loading
    for i in {1..3}; do
        # echo -ne "."
        echo -ne "\033[0;37m.\033[0m"
        sleep 0.30
    done
    echo

    for ((testNum=1; testNum<=TEST_COUNT; testNum++)); do
        # Generate test case
        ./generator > input
        ./wrong < input > out
        cat input out > data
        ./validator < data > res
        result=$(cat res)
        if [[ "$result" != "OK" ]]; then
            echo -e "\033[1;31m  Error found in test #$testNum!\033[0m"
            echo -e "\033[4;36m  Input:\033[0m"
            cat input
            echo -e "\033[4;36m  Output:\033[0m"
            cat out
            echo -e "\033[4;36m  Result:\033[0m $result"
            rm -f wrong validator generator input out res data 2>/dev/null
            exit
        fi
    done
    echo -e "\033[1;32m󰄲  Passed $TEST_COUNT tests successfully!\033[0m"

    # Cleanup
    rm -f wrong validator generator input out res data 2>/dev/null
}

# Save failed test for later inspection
save_failed_test() {
    local input=$1
    local output=$2
    local judge=$3
    
    mkdir -p failed_tests
    local prefix="failed_tests/test_$(date +%s)"
    
    cp "$input" "${prefix}.in"
    cp "$output" "${prefix}.out"
    if [[ -f "$judge" ]]; then
        cp "$judge" "${prefix}.judge"
    fi
    
    echo -e "\033[1;33m󰄲  Failed test saved to ${prefix}.{in,out}\033[0m"
}

# ================ MAIN SCRIPT ==================

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case "$1" in
        --help|-h)
            show_help
            exit 0
            ;;
        --version|-v)
            show_version
            exit 0
            ;;
        --parse)
            CMD="parse"
            shift
            if [[ -n "$1" && ("$1" == "here" || "$1" == "group") ]]; then
                SAMPLE_DIR="$1"
                shift
            fi
            ;;
        --cp)
            CMD="cp"
            shift
            ;;
        --stress)
            CMD="stress"
            shift
            # Handle optional arguments
            if [[ -n "$1" && "$1" != -* ]]; then WRONG_SOLUTION="$1"; shift; fi
            if [[ -n "$1" && "$1" != -* ]]; then SLOW_SOLUTION="$1"; shift; fi
            if [[ -n "$1" && "$1" != -* ]]; then GENERATOR="$1"; shift; fi
            if [[ -n "$1" && "$1" != -* && $1 =~ ^[0-9]+$ ]]; then TEST_COUNT="$1"; shift; fi
            ;;
        --validate)
            CMD="validate"
            shift
            if [[ -n "$1" && "$1" != -* ]]; then WRONG_SOLUTION="$1"; shift; fi
            if [[ -n "$1" && "$1" != -* ]]; then VALIDATOR="$1"; shift; fi
            if [[ -n "$1" && "$1" != -* ]]; then GENERATOR="$1"; shift; fi
            if [[ -n "$1" && "$1" != -* && $1 =~ ^[0-9]+$ ]]; then TEST_COUNT="$1"; shift; fi
            ;;
        -a)
            add_test_case
            shift
            ;;
        -d)
            COMPILE_SCRIPT="$DEBUG_COMPILE"
            shift
            ;;
        -m)
            MULTIPLE_SOLUTION=true
            shift
            ;;
        -r)
            RUN_ONLY=true
            shift
            ;;
        -t)
            if [[ -z "$2" || "$2" == -* ]]; then
                echo -e "\033[1;31m  Error: No time limit specified after -t\033[0m"
                exit 1
            fi
            if ! [[ "$2" =~ ^[0-9]+([.][0-9]+)?$ ]]; then
                echo -e "\033[1;31m  Error: Time limit after -t must be a number (e.g., 2 or 0.5)\033[0m"
                exit 1
            fi
            TIMEOUT_DURATION="$2"
            shift 2
            ;;
        *.cpp|*.c)
            SOURCE_FILE="$1"
            shift
            ;;
        *.py)
            SOURCE_FILE="$1"
            IS_PYTHON=true
            shift
            ;;
        # *.in)
        #     input_files+=("$1")
        #     shift
        #     ;;
        *)
            echo -e "\033[1;31m  Unknown option: $1\033[0m"
            show_help
            exit 1
            ;;
    esac
done

# Main execution
case "$CMD" in
    "parse")
        parse_problem
        ;;
    "cp")
        if [[ -z "$SOURCE_FILE" ]]; then
            echo -e "\033[1;31m  No source file specified for testing!\033[0m"
            exit 1
        fi

        executable="${SOURCE_FILE%.*}"
        if [[ "$IS_PYTHON" == false && ("$RUN_ONLY" == false || ! -f "$executable") ]]; then
            if ! compile_file "$SOURCE_FILE" "$executable" "$COMPILE_SCRIPT"; then
                exit 1
            fi
        fi
        # $COMPILE_SCRIPT "$executable" "$SOURCE_FILE"

        run_tests "$executable" "$IS_PYTHON"
        # exit $?
        exit 0
        ;;
    "stress")
        stress_test
        exit $?
        ;;
    "validate")
        validation_test
        exit $?
        ;;
    *)
        # Default mode - run the program
        if [[ -z "$SOURCE_FILE" ]]; then
            echo -e "\033[1;31m  No source file specified!\033[0m"
            show_help
            exit 1
        fi

        # Open an input window for user to enter input interactively, then run the source file with that input
        echo -e "\033[0;33m  If no input is required, or when you are done entering input, press Ctrl+D to continue:\033[0m"
        # echo -e "   "
        cat > input

        if [[ "$IS_PYTHON" == true ]]; then
            timeout "$TIMEOUT_DURATION" python3 "$SOURCE_FILE" < input
        else
            executable="${SOURCE_FILE%.*}"
            if [[ "$RUN_ONLY" == false || ! -f "$executable" ]]; then
                if ! compile_file "$SOURCE_FILE" "$executable" "$COMPILE_SCRIPT"; then
                    rm -f input
                    exit 1
                fi
            fi
            timeout "$TIMEOUT_DURATION" ./"$executable" < input
        fi
        rm -f input
        ;;
esac

exit 0
